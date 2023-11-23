#include "StateChecker.hpp"

int StateInfo::getStateCode()
{
    return _stateCode;
};

std::string StateInfo::getStateDescription()
{
    return _stateDescription;
};

void StateInfo::setStateCode(int stateCode)
{
    _stateCode = stateCode;
};

void StateInfo::setStateDescription(std::string stateDescription)
{
    _stateDescription = stateDescription;
};

StateInfo GameStateChecker::checkState(PieceMetadata metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        StateInfo currentState = gs->getState(metadata, color);
        if(currentState.getStateCode() > highestPriorityState.getStateCode())
        {
            highestPriorityState = currentState;
        }
    }

    return highestPriorityState;
};


StateInfo GameStateChecker::checkIllegalStates(PieceMetadata metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        if(gs->isIllegalForCurrentPlayer())
        {
            StateInfo currentState = gs->getState(metadata, color);
            if(currentState.getStateCode() > highestPriorityState.getStateCode())
            {
                highestPriorityState = currentState;
            }
        }
    }

    return highestPriorityState;
};