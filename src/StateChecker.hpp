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
protected:
    int state_code_;
    std::string state_description_;
public:
    StateInfo(int state_code, std::string state_description) : state_code_(state_code), state_description_(state_description){};
    int get_state_code();
    std::string get_state_description();
    void set_state_code(int state_code);
    void set_state_description(std::string state_description);
};



class StateChecker
{
public:
    virtual StateInfo CheckState(Board& board, PieceMetadata& metadata, Color color) const {return StateInfo(0, "");};
    virtual StateInfo CheckIllegalStates(Board& board, PieceMetadata& metadata, Color color) const {return StateInfo(0, "");};
};

class GameStateChecker : public StateChecker
{
protected:
    std::vector<std::unique_ptr<GameStateCheck> > _checks;
public:
    GameStateChecker(std::vector<std::unique_ptr<GameStateCheck> > checks);
    StateInfo CheckState(Board& board, PieceMetadata& metadata, Color color) const;
    StateInfo CheckIllegalStates(Board& board, PieceMetadata& metadata, Color color) const;
};