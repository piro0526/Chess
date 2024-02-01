#pragma once
#include "PieceMetadata.hpp"
#include <vector>
#include <string>
#include <memory>

class GameStateCheck;
class Board;
typedef int Color;

class StateInfo
{
private:
    int _stateCode;
    std::string _stateDescription;
public:
    StateInfo(int stateCode, std::string stateDescription) : _stateCode(stateCode), _stateDescription(stateDescription){};
    int getStateCode();
    std::string getStateDescription();
    void setStateCode(int stateCode);
    void setStateDescription(std::string stateDescription);
};



class StateChecker
{
private:
public:
    virtual StateInfo checkState(Board& board, PieceMetadata& metadata, Color color) const {return StateInfo(0, "");};
    virtual StateInfo checkIllegalStates(Board& board, PieceMetadata& metadata, Color color) const {return StateInfo(0, "");};
};

class GameStateChecker : public StateChecker
{
private:
    std::vector<std::unique_ptr<GameStateCheck>> _checks;
public:
    GameStateChecker(std::vector<std::unique_ptr<GameStateCheck>> checks);
    StateInfo checkState(Board& board, PieceMetadata& metadata, Color color) const;
    StateInfo checkIllegalStates(Board& board, PieceMetadata& metadata, Color color) const;
};