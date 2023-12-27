#include "StateChecker.hpp"
#include "GameStateCheck.hpp"

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

GameStateChecker::GameStateChecker(std::vector<std::unique_ptr<GameStateCheck>> checks)
{
    _checks = checks;
};

StateInfo GameStateChecker::checkState(Board& board, PieceMetadata metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        StateInfo currentState = gs->getState(board, metadata, color);
        if(currentState.getStateCode() > highestPriorityState.getStateCode())
        {
            highestPriorityState = currentState;
        }
    }

    return highestPriorityState;
};


StateInfo GameStateChecker::checkIllegalStates(Board& board, PieceMetadata metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        if(gs->isIllegalForCurrentPlayer())
        {
            StateInfo currentState = gs->getState(board, metadata, color);
            if(currentState.getStateCode() > highestPriorityState.getStateCode())
            {
                highestPriorityState = currentState;
            }
        }
    }

    return highestPriorityState;
};