#include "GameStateCheck.hpp"

StateInfo CheckState::getState(PieceMetadata metadata, Color color)
{
    StateInfo stateInfo(0, "");

    Spot kingSpot = metadata.findKingLocation(color);
    if(metadata.isSpotThreatend(color, kingSpot))
    {
        stateInfo.setStateDescription(color + " is checked");
        stateInfo.setStateCode(1);
    }

    return stateInfo;
};

bool CheckState::isIllegalForCurrentPlayer()
{
    return true;
};


StateInfo CheckMateState::getState(PieceMetadata metadata, Color color)
{
    return 
};

bool CheckMateState::isIllegalForCurrentPlayer()
{
    return 
};



StateInfo StaleMateState::getState(PieceMetadata metadata, Color color)
{
    return 
};

bool StaleMateState::isIllegalForCurrentPlayer()
{
    return 
};