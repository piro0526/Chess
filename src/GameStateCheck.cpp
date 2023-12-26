#include "GameStateCheck.hpp"

StateInfo CheckState::getState(Board board, PieceMetadata metadata, Color color)
{
    StateInfo stateInfo(0, "");

    Spot kingSpot = metadata.findKingLocation(color);
    if(metadata.isSpotThreatened(color, kingSpot))
    {
        stateInfo.setStateDescription((color == 1 ? "WHITE is checked" : "BLACK is checked"));
        stateInfo.setStateCode(1);
    }

    return stateInfo;
};

bool CheckState::isIllegalForCurrentPlayer()
{
    return true;
};


StateInfo CheckMateState::getState(Board board, PieceMetadata metadata, Color color)
{
    StateInfo stateInfo = StateInfo(0, "");
    Spot kingSpot = metadata.findKingLocation(color);
    bool isChecked = metadata.isSpotThreatened(color, kingSpot);
    if (!isChecked)
        return stateInfo;

    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            Spot next = Spot(kingSpot.getRank() + i, kingSpot.getFile() + j);
            if (metadata.isMoveValid(Move(kingSpot, next))
                    && !metadata.isSpotThreatened(color, next)) {
                return stateInfo;
            }
        }
    stateInfo.setStateDescription((color == 1 ? "CAECKMATE\n WHITE loses" : "CAECKMATE\n BLACK loses"));
    stateInfo.setStateCode(2);

    return stateInfo;
};

bool CheckMateState::isIllegalForCurrentPlayer()
{
    return false;
};



StateInfo StaleMateState::getState(Board board, PieceMetadata metadata, Color color)
{
    StateInfo stateInfo = StateInfo(0, "");
    Spot kingSpot = metadata.findKingLocation(color);
    bool isChecked = metadata.isSpotThreatened(color, kingSpot);
    if (isChecked)
        return stateInfo;

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::shared_ptr<Piece> piece = board.getPiece(Spot(i, j));
            if (piece != nullptr && piece->getColor() == color && metadata.canPieceMove(Spot(i, j), color)) {
                return stateInfo;
            }
        }
    stateInfo.setStateDescription("STALEMATE\nDRAW");
    stateInfo.setStateCode(2);
    return stateInfo;
};

bool StaleMateState::isIllegalForCurrentPlayer()
{
    return false;
};