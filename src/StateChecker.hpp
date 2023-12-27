#pragma once
#include <vector>
#include <string>

class GameStateCheck;

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
    virtual StateInfo checkState(Board& board, PieceMetadata metadata, Color color) const;
    virtual StateInfo checkIllegalStates(Board& board, PieceMetadata metadata, Color color) const;
};

class GameStateChecker : public StateChecker
{
private:
    std::vector<std::unique_ptr<GameStateCheck>> _checks;
public:
    GameStateChecker(std::vector<std::unique_ptr<GameStateCheck>> checks);
    StateInfo checkState(Board& board, PieceMetadata metadata, Color color) const;
    StateInfo checkIllegalStates(Board& board, PieceMetadata metadata, Color color) const;
};