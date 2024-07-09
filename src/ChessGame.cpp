#include "ChessGame.hpp"


ChessGame::ChessGame()
{
    board_ = Board();
    std::cout << "Board created" << std::endl;
    white_interface_ = std::make_shared<CUI>(WHITE);
    black_interface_ = std::make_shared<CUI>(BLACK);
    Init();
};

ChessGame::ChessGame(const std::shared_ptr<Interface>& white_interface, const std::shared_ptr<Interface>& black_interface)
{
    board_ = Board();
    std::cout << "Board created" << std::endl;
    white_interface_ = std::move(white_interface);
    black_interface_ = std::move(black_interface);
    Init();
    std::cout << "Initialized" << std::endl;
    //board_.MovePiece(Move(Spot(int('7'-'1'),int('e'-'a')), Spot(int('5'-'1'),int('e'-'a'))));
};

void ChessGame::Init()
{
    metadata_ = PieceMetadata(&board_);

    std::vector<std::unique_ptr<GameStateCheck> > checks;
    checks.emplace_back(std::move(std::make_unique<CheckState>()));
    checks.emplace_back(std::move(std::make_unique<CheckMateState>()));
    checks.emplace_back(std::move(std::make_unique<StaleMateState>()));
    state_checker_ = std::move(std::make_unique<GameStateChecker>(std::move(checks)));

    auto reg = std::make_unique<RegularMoveHandler>();
    auto enPassant = std::make_unique<EnPassantMoveHandler>();
    auto promotion = std::make_unique<PromotionMoveHandler>();
    auto castling = std::make_unique<CastlingMoveHandler>();
    enPassant->SetNext(std::move(reg));
    promotion->SetNext(std::move(enPassant));
    castling->SetNext(std::move(promotion));
    move_handler_ = std::move(castling);
};

void ChessGame::Start()
{
    std::shared_ptr<Interface> current_interface = white_interface_;
    StateInfo game_state(0, "");

    std::cout << "Game begin" << std::endl;

    while(game_state.get_state_code() <= 1)
    {
        while(1)
        {
            if(PlayTurn(current_interface, game_state)) break;
        }
        game_state = state_checker_->CheckState(board_, metadata_, SwapInterface(current_interface)->get_color());
        if(game_state.get_state_code() != 0)
        {
            std::cout << game_state.get_state_description() << std::endl;
        }
        current_interface = SwapInterface(current_interface);
        if(game_state.get_state_code() == 2)
        {
            std::cout << "GG" << std::endl;
        }
    }
};

bool ChessGame::PlayTurn(const std::shared_ptr<Interface>& current_interface, StateInfo current_state)
{
    std::cout << ((current_interface->get_color() == 1) ? "w" : "b")  << " turn" << std::endl;
    Action player_action = interpreter_.ToGame(current_interface->Input(interpreter_.ToInterface(board_, current_state)));
    Move move = player_action.get_move();
    Spot startSpot = move.get_start();
    Spot endspot = move.get_end();
    std::shared_ptr<Piece> start_piece = board_.GetPiece(move.get_start());
    std::shared_ptr<Piece> end_piece = board_.GetPiece(move.get_end());

    if(board_.IsSpotEmpty(startSpot) || board_.GetPiece(startSpot)->get_color() != current_interface->get_color())
    {
        current_interface->Input("invalid move1");
        return false;
    }
    int action_type = move_handler_->HandleMove(board_, metadata_, player_action);

    if(action_type<0)
    {
        current_interface->Input("invalid move2");
        return false;
    }

    //invalid state
    StateInfo game_state = state_checker_-> CheckIllegalStates(board_, metadata_, current_interface->get_color());
    if(game_state.get_state_code() != 0)
    {
        Undo(move, start_piece, end_piece);
        current_interface->Input(game_state.get_state_description());
        return false;
    }


    hist_.push_back({std::to_string(action_type), player_action.get_saction(), interpreter_.FEN(board_)});

    return true;
};


void ChessGame::Undo(Move move, const std::shared_ptr<Piece>& start_piece, const std::shared_ptr<Piece>& end_piece)
{
    if (end_piece != nullptr)
        board_.UnCapturePiece(end_piece);
    board_.SetPiece(start_piece, move.get_start());
    board_.SetPiece(end_piece, move.get_end());
};

std::shared_ptr<Interface> ChessGame::SwapInterface(const std::shared_ptr<Interface>& interface)
{
    if(interface->get_color() == WHITE)
    {
        return black_interface_;
    }
    else
    {
        return white_interface_;
    }
};