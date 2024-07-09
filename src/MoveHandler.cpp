#include "MoveHandler.hpp"

void MoveHandler::SetNext(const std::shared_ptr<IMoveHandler>& next_move_handler)
{
    next_move_handler_ = std::move(next_move_handler);
};

int  CastlingMoveHandler::HandleMove(Board& board, PieceMetadata& metadata, Action action)
{

    Move move = action.get_move();
    if(IsCastlingMove(board, metadata, move))
    {
        Rank rank = move.get_start().get_rank();
        File file = move.get_start().get_file();
        int yDistance = move.get_start().get_file() - move.get_end().get_file();
        int direction = yDistance < 0 ? 1 : -1;
        Move rookMove(move.get_end(), Spot(rank, file + direction));
        Move kingMove(move.get_end(), Spot(rank, file + 3 * direction));
        board.MovePiece(rookMove);
        board.MovePiece(kingMove);
        board.CapturePiece(nullptr);
        return 1;
    }
    if(next_move_handler_ != nullptr)
    {
        return next_move_handler_->HandleMove(board, metadata, action);
    }


    return -1;
};

bool CastlingMoveHandler::IsCastlingMove(Board& board, PieceMetadata& metadata, Move move)
{
    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    if(board.IsSpotEmpty(end_spot))
    {
        return false;
    }
    std::shared_ptr<Piece> piece1 = board.GetPiece(start_spot);
    std::shared_ptr<Piece> piece2 = board.GetPiece(end_spot);

    if(piece1->get_symbol() != "King" || piece2->get_symbol() != "Rook" || piece1->get_moved_amount() > 0 || piece2->get_moved_amount() > 0 || piece1->get_color() == piece2->get_color())
    {
        return false;
    }

    int yDistance = end_spot.get_file() - start_spot.get_file();
    int direction = yDistance > 0 ? 1 : -1;

    for(int i=0; i<4; i++)
    {
        Rank rank = start_spot.get_rank();
        File file = start_spot.get_file() + 1 * direction;
        if(metadata.IsSpotThreatened(piece1->get_color(), Spot(rank, file)).size() > 0 || (!board.IsSpotEmpty(Spot(rank, file)) && file != start_spot.get_file() && file != end_spot.get_file()))
        {
            return false;
        }
    }

    return true;
};

int EnPassantMoveHandler::HandleMove(Board& board, PieceMetadata& metadata, Action action)
{

    Move move = action.get_move();
    if(IsEnPassantMove(board, move))
    {
        board.MovePiece(move);
        Rank rank = move.get_start().get_rank();
        File file = move.get_end().get_file();
        board.CapturePiece(board.GetPiece(Spot(rank, file)));
        board.ResetTile(Spot(rank, file));

        return 2;
    }
    if(next_move_handler_ != nullptr)
    {
        return next_move_handler_->HandleMove(board, metadata, action);
    }

    return -1;
};

bool EnPassantMoveHandler::IsEnPassantMove(Board& board, Move move)
{
    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();

    if (board.IsOutofRange(move) || !(board.GetPiece(start_spot)->get_symbol() == "Pawn"))
    {
        return false;
    }
    std::shared_ptr<Piece> pawn = board.GetPiece(start_spot);

    int xDistance = end_spot.get_rank() - start_spot.get_rank();
    int yDistance = end_spot.get_file() - start_spot.get_file();

    int side = pawn->get_color() == WHITE ? -1 : 1;

    if(xDistance != side || abs(yDistance) != 1 || !board.IsSpotEmpty(end_spot))
    {
        return false;
    }

    std::shared_ptr<Piece> enemyPawn = board.GetPiece(Spot(start_spot.get_rank(), end_spot.get_file()));

    if(!(enemyPawn->get_symbol() == "Pawn") || pawn->IsAllyPiece(enemyPawn) || enemyPawn->get_moved_amount() != 1)
    {
        return false;
    }

    return true;
}

int PromotionMoveHandler::HandleMove(Board& board, PieceMetadata& metadata, Action action)
{
    Move move = action.get_move();
    std::string piece_type = action.get_piece_type();
    if(IsPromotionMove(board, metadata, move))
    {
        int file = move.get_end().get_file();
        int rank = move.get_end().get_rank();
        board.MovePiece(move);
        board.CapturePiece(board.GetPiece(move.get_end()));
        Color color = board.GetPiece(move.get_end())->get_color();
        PieceFactory factory;
        std::unique_ptr<Piece> tmp_piece = factory.CreatePiece(piece_type, color);
        board.SetPiece(std::move(tmp_piece), Spot(rank, file));
        return 3;
    }
    if(next_move_handler_ != nullptr)
    {
        return next_move_handler_->HandleMove(board, metadata, action);
    }

    return -1;
};

bool PromotionMoveHandler::IsPromotionMove(Board& board, PieceMetadata& metadata, Move move)
{
    if(!metadata.IsMoveValid(move))
    {
        return false;
    }

    Spot start_spot = move.get_start();
    Spot end_spot = move.get_end();
    std::shared_ptr<Piece> piece = board.GetPiece(start_spot);

    if(!(piece->get_symbol() == "Pawn"))
    {
        return false;
    }

    int edge = piece->get_color() == WHITE ? 0 : BOARD_SIZE - 1;

    return end_spot.get_file() == edge;
};

int RegularMoveHandler::HandleMove(Board& board, PieceMetadata& metadata, Action action)
{
    Move move = action.get_move();
    if (metadata.IsMoveValid(move) && !board.GetPiece(move.get_start())->IsAllyPiece(board.GetPiece(move.get_end())))
    {
        bool is_take_piece = (board.GetPiece(move.get_end())!=nullptr);
        board.MovePiece(move);
        if(!is_take_piece){
            board.CapturePiece(nullptr);
        }
        return 0;
    }
    if (next_move_handler_ != nullptr)
    {
        return next_move_handler_->HandleMove(board, metadata, action);
    }

    return -1;
};