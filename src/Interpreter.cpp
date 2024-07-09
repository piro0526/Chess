#include "Interpreter.hpp"

std::string Interpreter::ToInterface(Board& board, StateInfo state_info) const
{
    std::string fet, state_desc;
    fet = FEN(board);
    state_desc = state_info.get_state_description();
    return fet+"\n"+state_desc;
}

Action Interpreter::ToGame(std::string input){
    std::string start_coodinates = input.substr(0,2);
    std::string end_coodinates = input.substr(2,2);
    std::string piece_type_short = "";
    if(input.length()>4){
        piece_type_short = input.substr(5,2);
    }
    std::string piece_type = "";
    int s_f = int(start_coodinates[0] - 'a');
    int s_r = int(start_coodinates[1] - '1');
    int e_f = int(end_coodinates[0] - 'a');
    int e_r = int(end_coodinates[1] - '1');
    if(piece_type_short == "Q"){
        piece_type = "Queen";
    }else if(piece_type == "K"){
        piece_type = "King";
    }else if(piece_type == "R"){
        piece_type = "Rook";
    }else if(piece_type == "B"){
        piece_type = "Bishop";
    }else if(piece_type == "p"){
        piece_type = "Pawn";
    }
    return Action(Move(Spot(s_r, s_f), Spot(e_r, e_f)), piece_type);
}

std::string Interpreter::FEN(Board& board) const{
    std::string fen = "";
    int empty_cnt = 0;
    for(Rank r=BOARD_SIZE-1; r>=0; r--)
    {
        empty_cnt = 0;
        for(File f=0; f<BOARD_SIZE; f++)
        {
            if(board.GetPiece(Spot(r, f)) == nullptr)
            {
                empty_cnt++;
                continue;
            }

            if(empty_cnt>0)
            {
                fen.push_back(empty_cnt+'0');
                empty_cnt = 0;
            }

            std::string s = board.GetPiece(Spot(r, f))->get_symbol();
            Color b = board.GetPiece(Spot(r, f))->get_color();


            if(s=="Pawn")
            {
                if(b==WHITE)
                {
                    fen.push_back('P');
                }
                else if(b==BLACK)
                {
                    fen.push_back('p');
                }
            }
            else if(s=="Rook")
            {
                if(b==WHITE)
                {
                    fen.push_back('R');
                }
                else if(b==BLACK)
                {
                    fen.push_back('r');
                }
            }
            else if(s=="Knight")
            {
                if(b==WHITE)
                {
                    fen.push_back('N');
                }
                else if(b==BLACK)
                {
                    fen.push_back('n');
                }
            }
            else if(s=="Bishop")
            {
                if(b==WHITE)
                {
                    fen.push_back('B');
                }
                else if(b==BLACK)
                {
                    fen.push_back('b');
                }
            }
            else if(s=="Queen")
            {
                if(b==WHITE)
                {
                    fen.push_back('Q');
                }
                else if(b==BLACK)
                {
                    fen.push_back('q');
                }
            }
            else if(s=="King")
            {
                if(b==WHITE)
                {
                    fen.push_back('K');
                }
                else if(b==BLACK)
                {
                    fen.push_back('k');
                }
            }
        }

        if(empty_cnt > 0)
        {
            fen.push_back(empty_cnt+'0');
            empty_cnt = 0;
        }

        if(r != 0)
        {
            fen.push_back('/');
        }
    }
    return fen;
}