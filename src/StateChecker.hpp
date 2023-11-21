#pragma once
#include "GameStateCheck.hpp"
#include <vector>
#include <string>


class StateInfo
{
private:
    int _stateCode;
    std::string _stateMessage;
public:
    StateInfo(int stateCode, std::string stateMessage) : _stateCode(stateCode), _stateMessage(stateMessage){};
};



class StateChecker
{
private:
public:
    virtual StateInfo checkState(PieceMetadata metadata, Color color) const;
    virtual StateInfo checkIllegalStates(PieceMetadata metadata, Color color) const;
};

class GameStateChecker : public StateChecker
{
private:
    std::vector<GameStateCheck> _checks;
public:
    StateInfo checkState(Color color) const;
    StateInfo checkIllegalStates(Color color) const;
};