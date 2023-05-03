//
// Created by haven on 4/14/23.
//

#ifndef PROBABILITYCHESS_PIECE_H
#define PROBABILITYCHESS_PIECE_H

#include <vector>
#include <string>

class Piece
{
public:
    Piece(): exist(false), id(0) {}
    // default constructor for an empty piece which populates the empty squares of the board

    Piece(bool inpColor, int inpId): exist(true), color(inpColor), id(inpId), moveCount(0) {}
    // constructor for a standard piece
    // input inpColor:

    std::vector<int> getMoves()
    {
        // effectively a data repository of every single possible movement offset a given piece type could make

        switch (id)
        {
            case 1:
                // pawn moves
                if (color)
                {
                    return {8, 16, 7, 9};
                }
                else
                {
                    return {-8, -16, -7, -9};
                }
            case 2:
                // knight moves
                return {-17, -15, -10, -6, 6, 10, 15, 17};
            case 3:
                // bishop moves
                return {-9, -18, -27, -36, -45, -54, -63, 9, 18, 27, 36, 45, 54, 63, -7, -14, -21, -28, -35, -42, -49,
                        7, 14, 21, 28, 35, 42, 49};
            case 4:
                // rook moves
                return {-1, -2, -3, -4, -5, -6, -7, 1, 2, 3, 4, 5, 6, 7, -8, -16, -24, -32, -40, -48, -56, 8, 16, 24,
                        32, 40, 48, 56};
            case 5:
                // queen moves
                return {-9, -18, -27, -36, -45, -54, -63, 9, 18, 27, 36, 45, 54, 63, -7, -14, -21, -28, -35, -42, -49,
                        7, 14, 21, 28, 35, 42, 49, -1, -2, -3, -4, -5, -6, -7, 1, 2, 3, 4, 5, 6, 7, -8, -16, -24, -32,
                        -40, -48, -56, 8, 16, 24, 32, 40, 48, 56};
            case 6:
                // king moves
                return {-9, -8, -7, -2, -1, 1, 2, 7, 8, 9};
            default:
                return {};
        }
    }

    std::string display()
    {
        // turns a piece into its string representation for use with Board.display()

        if (!exist)
        {
            return "  ";
        }
        if (color)
        {
            switch (id)
            {
                case 1:
                    return "Pb";
                case 2:
                    return "Nb";
                case 3:
                    return "Bb";
                case 4:
                    return "Rb";
                case 5:
                    return "Qb";
                case 6:
                    return "Kb";
                default:
                    return "  ";
            }
        }
        else
        {
            switch (id)
            {
                case 1:
                    return "Pw";
                case 2:
                    return "Nw";
                case 3:
                    return "Bw";
                case 4:
                    return "Rw";
                case 5:
                    return "Qw";
                case 6:
                    return "Kw";
                default:
                    return "  ";
            }
        }
    }

    // getters

    bool exists()
    {
        return exist;
    }

    bool getColor()
    {
        return color;
    }

    int getId()
    {
        return id;
    }

    int getMoveCount()
    {
        return moveCount;
    }

    void setId(int inpId)
    {
        id = inpId;
    }

    void incMoveCount()
    {
        moveCount++;
    }

protected:
    bool exist, color;
    // color = 0: white
    // color = 1: black

    // exist = 0: doesn't exist
    // exist = 1: does exist

    int id, moveCount;
    // id = 1: pawn
    // id = 2: knight
    // id = 3: bishop
    // id = 4: rook
    // id = 5: queen
    // id = 6: king

};

#endif //PROBABILITYCHESS_PIECE_H
