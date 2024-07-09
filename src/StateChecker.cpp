#include "StateChecker.hpp"
#include "GameStateCheck.hpp"

int StateInfo::get_state_code()
{
    return state_code_;
};

std::string StateInfo::get_state_description()
{
    return state_description_;
};

void StateInfo::set_state_code(int state_code)
{
    state_code_ = state_code;
};

void StateInfo::set_state_description(std::string state_description)
{
    state_description_ = state_description;
};

GameStateChecker::GameStateChecker(std::vector<std::unique_ptr<GameStateCheck>> checks)
{
    _checks = std::move(checks);
};

StateInfo GameStateChecker::CheckState(Board& board, PieceMetadata& metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        StateInfo currentState = gs->get_state(board, metadata, color);
        if(currentState.get_state_code() > highestPriorityState.get_state_code())
        {
            highestPriorityState = currentState;
        }
    }

    return highestPriorityState;
};


StateInfo GameStateChecker::CheckIllegalStates(Board& board, PieceMetadata& metadata, Color color) const
{
    StateInfo highestPriorityState(-1, "");
    for(auto& gs: _checks)
    {
        if(gs->IsIllegalForCurrentPlayer())
        {
            StateInfo currentState = gs->get_state(board, metadata, color);
            if(currentState.get_state_code() > highestPriorityState.get_state_code())
            {
                highestPriorityState = currentState;
            }
        }
    }

    return highestPriorityState;
};