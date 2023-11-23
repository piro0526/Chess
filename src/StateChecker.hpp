#pragma once
#include "GameStateCheck.hpp"
#include <vector>
#include <string>


class StateInfo
{
private:
    int _stateCode;
    std::string _stateDescription;
public:
    StateInfo(int stateCode, std::string stateMessage) : _stateCode(stateCode), _stateMessage(stateMessage){};
    int getStateCode();
    std::string getStateDescription();
    void setStateCode(int stateCode);
    void setStateDescription(std::string stateDescription);
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
    std::vector<std::unique_ptr<GameStateCheck>> _checks;
public:
    GameStateChecker(std::vector<std::unique_ptr<GameStateCheck>> checks) : _checks(checks){};
    StateInfo checkState(PieceMetadata metadata, Color color) const;
    StateInfo checkIllegalStates(PieceMetadata metadata, Color color) const;
};