#include "ValidMoveChecker.hpp"

ValidMoveChecker::ValidMoveChecker(Board *board){
    board_ = board;

    metadata_ = PieceMetadata(board_);

    std::vector<std::unique_ptr<GameStateCheck>> checks;
    checks.emplace_back(std::move(std::make_unique<CheckState>()));
    checks.emplace_back(std::move(std::make_unique<CheckMateState>()));
    checks.emplace_back(std::move(std::make_unique<StaleMateState>()));
    state_checker_ = std::move(std::make_unique<GameStateChecker>(std::move(checks)));

    std::unique_ptr<MoveHandler> reg = std::make_unique<RegularMoveHandler>();
    std::unique_ptr<MoveHandler> enPassant = std::make_unique<EnPassantMoveHandler>();
    std::unique_ptr<MoveHandler> promotion = std::make_unique<PromotionMoveHandler>();
    std::unique_ptr<MoveHandler> castling = std::make_unique<CastlingMoveHandler>();
    enPassant->SetNext(std::move(reg));
    promotion->SetNext(std::move(enPassant));
    castling->SetNext(std::move(promotion));
    move_handler_ = std::move(castling);
}

int ValidMoveChecker::IsValidMove(Action action){

}