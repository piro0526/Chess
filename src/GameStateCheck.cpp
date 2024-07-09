#include "GameStateCheck.hpp"
#include "StateChecker.hpp"

StateInfo CheckState::get_state(Board& board, PieceMetadata& metadata, Color color)
{
    StateInfo stateInfo(0, "");

    Spot kingSpot = metadata.FindKingLocation(color);
    if(metadata.IsSpotThreatened(color, kingSpot).size() > 0)
    {
        stateInfo.set_state_description((color == 1 ? "WHITE is checked" : "BLACK is checked"));
        stateInfo.set_state_code(1);
    }

    return stateInfo;
};

bool CheckState::IsIllegalForCurrentPlayer()
{
    return true;
};


StateInfo CheckMateState::get_state(Board& board, PieceMetadata& metadata, Color color)
{
    StateInfo stateInfo = StateInfo(0, "");
    Spot kingSpot = metadata.FindKingLocation(color);
    std::vector<Spot> ememy_spots = metadata.IsSpotThreatened(color, kingSpot);
    if (ememy_spots.size()==0){
        return stateInfo;
    }

    for (const auto& s : ememy_spots) {
        if(metadata.IsSpotThreatened(-color, s).size()==0){
            return stateInfo;
        }
    }

    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            Spot next = Spot(kingSpot.get_rank() + i, kingSpot.get_file() + j);
            if (metadata.IsMoveValid(Move(kingSpot, next)) && metadata.IsSpotThreatened(color, next).size()==0) {
                return stateInfo;
            }
        }
    stateInfo.set_state_description((color == 1 ? "CAECKMATE\nWHITE loses" : "CAECKMATE\nBLACK loses"));
    stateInfo.set_state_code(2);

    return stateInfo;
};

bool CheckMateState::IsIllegalForCurrentPlayer()
{
    return false;
};



StateInfo StaleMateState::get_state(Board& board, PieceMetadata& metadata, Color color)
{
    StateInfo stateInfo = StateInfo(0, "");
    Spot kingSpot = metadata.FindKingLocation(color);
    bool isChecked = metadata.IsSpotThreatened(color, kingSpot).size() > 0;
    if (isChecked)
        return stateInfo;

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::shared_ptr<Piece> piece = board.GetPiece(Spot(i, j));
            if (piece != nullptr) {
                if(piece->get_color() == color && metadata.CanPieceMove(Spot(i, j), color))
                {
                    return stateInfo;
                }
            }
        }
    stateInfo.set_state_description("STALEMATE\nDRAW");
    stateInfo.set_state_code(2);
    return stateInfo;
};

bool StaleMateState::IsIllegalForCurrentPlayer()
{
    return false;
};