#include "ChessGame.hpp"


ChessGame::ChessGame()
{
    _board = Board();
    _metadata = PieceMetadata(&_board);
    _whitePlayer = std::make_shared<stdinPlayer>(WHITE);
    _blackPlayer = std::make_shared<stdinPlayer>(BLACK);
    init();
};

ChessGame::ChessGame(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> blackPlayer)
{
    _board = Board();
    _metadata = PieceMetadata(&_board);
    _whitePlayer = std::move(whitePlayer);
    _blackPlayer = std::move(blackPlayer);
    init();
};

void ChessGame::init()
{
    std::vector<std::unique_ptr<GameStateCheck>> checks;
    checks.emplace_back(std::move(std::make_unique<CheckState>()));
    checks.emplace_back(std::move(std::make_unique<CheckMateState>()));
    checks.emplace_back(std::move(std::make_unique<StaleMateState>()));
    _stateChecker = std::move(std::make_unique<GameStateChecker>(std::move(checks)));

    
    std::unique_ptr<MoveHandler> reg = std::make_unique<RegularMoveHandler>();
    std::unique_ptr<MoveHandler> enPassant = std::make_unique<EnPassantMoveHandler>();
    std::unique_ptr<MoveHandler> promotion = std::make_unique<PromotionMoveHandler>();
    std::unique_ptr<MoveHandler> castling = std::make_unique<CastlingMoveHandler>();
    enPassant->setNext(std::move(reg));
    promotion->setNext(std::move(enPassant));
    castling->setNext(std::move(promotion));
    _moveHandler = std::move(castling);
    
};

void ChessGame::start()
{
    std::shared_ptr<Player> _currentPlayer = _whitePlayer;
    StateInfo gameState(0, "");

    while(gameState.getStateCode() <= 1)
    {
        std::string message = "";
        while(1)
        {
            message = playTurn(_currentPlayer, message);
            if(message == "success")
            {
                break;
            }
            else if(message == "promotion")
            {
                promotion();
            }
        }
        gameState = _stateChecker->checkState(_board, _metadata, swapPlayer(_currentPlayer)->getColor());
        if(gameState.getStateCode() != 0)
        {
            std::cout << gameState.getStateDescription() << std::endl;
        }
        _currentPlayer = swapPlayer(_currentPlayer);
        if(gameState.getStateCode() == 2)
        {
            std::cout << "GG" << std::endl;
        }
    }
};

std::string ChessGame::playTurn(std::shared_ptr<Player> player, std::string error)
{
    std::string input = getPlayerInput(player, "getnextmove", error);
    Move move = Move(parseCoordinates(input.substr(0,2)), parseCoordinates(input.substr(3,2)));
    Spot startSpot = move.getStart();
    std::shared_ptr<Piece> startPiece = _board.getPiece(move.getStart());
    std::shared_ptr<Piece> endPiece = _board.getPiece(move.getEnd());
    
    if(_board.isSpotEmpty(startSpot) || !_board.getPiece(startSpot)->getColor() == player->getColor() || !_moveHandler->handleMove(_board, _metadata, move))
    {
        return "invalid input";
    }
    else
    {
        StateInfo gameState = _stateChecker->checkIllegalStates(_board, _metadata, player->getColor());
        if(gameState.getStateCode() != 0)
        {
            undo(move, startPiece, endPiece);
            return gameState.getStateDescription();
        }
    }

    if(move.getEnd().getFile() == (startPiece->getColor() == WHITE ? 0 : BOARD_SIZE - 1) && startPiece->getSymbol() == "Pawn")
    {
        return "promotion";
    }

    return "success";
};

std::string ChessGame::getPlayerInput(std::shared_ptr<Player> player, std::string command, std::string error)
{
    std::map<std::string, std::string> message;
    std::string fen = _board.getFEN();
    message["FEN"] = fen;
    message["command"] = command;
    message["errorMessage"] = error;
    return player->getPlayerInput(message);
};

std::string ChessGame::promotion(std::shared_ptr<Player> player, std::string error)
{
    std::string input = getPlayerInput(player, "promotion", error);
    
}

Spot ChessGame::parseCoordinates(std::string strCoodinates)
{
    int x = strCoodinates[0] - 'a';
    int y = strCoodinates[1] - '1';
    return Spot(x, y);
};

void ChessGame::undo(Move move, std::shared_ptr<Piece> startPiece, std::shared_ptr<Piece> endPiece)
{
    if (endPiece != nullptr)
            _board.unCapturePiece(endPiece);
        _board.setPiece(startPiece, move.getStart());
        _board.setPiece(endPiece, move.getEnd());
};

std::shared_ptr<Player> ChessGame::swapPlayer(std::shared_ptr<Player> player)
{
    if(player->getColor() == WHITE)
    {
        return _blackPlayer;
    }
    else
    {
        return _whitePlayer;
    }
};