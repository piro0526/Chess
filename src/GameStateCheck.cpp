#include "GameStateCheck.hpp"

StateInfo CheckState::getState(PieceMetadata metadata, Color color)
{
    StateInfo stateInfo(0, "");

    Spot kingSpot = metadata.findKingLocation(color);
    if(metadata.isSpotThreatend(color, kingSpot))
    {
        stateInfo.setStateDiscription(color + " is checked");
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
    
};

bool CheckMateState::isIllegalForCurrentPlayer()
{
    
};



StateInfo StaleMateState::getState(PieceMetadata metadata, Color color)
{
    
};

bool StaleMateState::isIllegalForCurrentPlayer()
{
    
};