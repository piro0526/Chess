#include "Board.hpp"
#include "Piece.hpp"

Board::Board()
{
    initBoard();
};

void Board::initBoard()
{
    PieceFactory fac;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            _rawBoard[i][j] = nullptr;
        }
    }

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            setPiece(fac.createPiece(_configuretion[i][j], WHITE), Spot(j, 1 - i));
        }
    }

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            setPiece(fac.createPiece(_configuretion[i][j], BLACK), Spot(j ,BOARD_SIZE - 2 + i));
        }
    }
};

bool Board::isOutofRange(Move move) const
{
    return isOutofRange(move.getStart()) || isOutofRange(move.getEnd());
};

bool Board::isOutofRange(Spot spot) const
{
    return spot.getFile() < 0 || spot.getFile() >= BOARD_SIZE || spot.getRank() < 0 || spot.getRank() >= BOARD_SIZE;
};

bool Board::isSpotEmpty(Spot spot) const
{
    return _rawBoard[spot.getRank()][spot.getFile()] == nullptr;
};

void Board::setPiece(std::shared_ptr<Piece> piece, Spot spot)
{
    _rawBoard[spot.getRank()][spot.getFile()] = piece;
};

bool Board::movePiece(Move move)
{
    if(isOutofRange(move))
    {
        return false;
    };

    std::shared_ptr<Piece> piece = getPiece(move.getStart());

    if(piece == nullptr)
    {
        return false;
    }

    if(!isSpotEmpty(move.getEnd()))
    {
        capturePiece(getPiece(move.getEnd()));
        resetTile(move.getEnd());
    }
    
    setPiece(piece, move.getEnd());
    setPiece(nullptr, move.getStart());

    return true;
};

void Board::capturePiece(std::shared_ptr<Piece> piece)
{
    _capturedPieces.push_back(piece);
};

void Board::unCapturePiece(std::shared_ptr<Piece> piece)
{
    std::remove(std::begin(_capturedPieces), std::end(_capturedPieces), piece);
};

void Board::resetTile(Spot spot)
{
    _rawBoard[spot.getRank()][spot.getFile()] = nullptr;
};

void Board::viewBoard()
{
    return;
};

std::shared_ptr<Piece> Board::getPiece(Spot spot) const
{
    return _rawBoard[spot.getRank()][spot.getFile()];
};

int Board::getTurn() const
{
    return _turns;
};

std::string Board::getFEN()
{
    std::string fen = "";
    int empty_cnt = 0;
    for(int f=BOARD_SIZE-1; f>=0; f--)
    {
        empty_cnt = 0;
        for(int r=0; r<BOARD_SIZE; r++)
        {
            if(getPiece(Spot(r, f)) == nullptr)
            {
                empty_cnt++;
                continue;
            }

            if(empty_cnt>0)
            {
                fen.push_back(empty_cnt+'0');
                empty_cnt = 0;
            }

            std::string s = getPiece(Spot(r, f))->getSymbol();
            Color b = getPiece(Spot(r, f))->getColor();


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

        if(f != 0)
        {
            fen.push_back('/');
        }
    }
    return fen;
};