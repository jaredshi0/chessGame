 //
// Created by haven on 4/14/23.
//

#ifndef PROBABILITYCHESS_BOARD_H
#define PROBABILITYCHESS_BOARD_H

#include "Piece.h"
#include <map>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

class Board
{
public:
    Board(int inpId = 0): mode(inpId), turn(0)
    {
        // constructor for board object
        // input inpId: integer corresponding to which board setup you'd like. im thinking of adding more setups for other modes, but by default it is the standard chess layout

        for (int ii = 0; ii < 64; ii++)
        {
            boardState[ii] = Piece();
        }
        switch (inpId)
        {
            default:
                // standard chess board
                boardState[0] = Piece(1, 4);
                boardState[1] = Piece(1, 2);
                boardState[2] = Piece(1, 3);
                boardState[3] = Piece(1, 5);
                boardState[4] = Piece(1, 6);
                boardState[5] = Piece(1, 3);
                boardState[6] = Piece(1, 2);
                boardState[7] = Piece(1, 4);
                boardState[8] = Piece(1, 1);
                boardState[9] = Piece(1, 1);
                boardState[10] = Piece(1, 1);
                boardState[11] = Piece(1, 1);
                boardState[12] = Piece(1, 1);
                boardState[13] = Piece(1, 1);
                boardState[14] = Piece(1, 1);
                boardState[15] = Piece(1, 1);
                boardState[48] = Piece(0, 1);
                boardState[49] = Piece(0, 1);
                boardState[50] = Piece(0, 1);
                boardState[51] = Piece(0, 1);
                boardState[52] = Piece(0, 1);
                boardState[53] = Piece(0, 1);
                boardState[54] = Piece(0, 1);
                boardState[55] = Piece(0, 1);
                boardState[56] = Piece(0, 4);
                boardState[57] = Piece(0, 2);
                boardState[58] = Piece(0, 3);
                boardState[59] = Piece(0, 5);
                boardState[60] = Piece(0, 6);
                boardState[61] = Piece(0, 3);
                boardState[62] = Piece(0, 2);
                boardState[63] = Piece(0, 4);
                break;
            case (1):
                // pawn test
                boardState[36] = Piece(0, 1);
                break;
            case (2):
                // knight test
                boardState[36] = Piece(0, 2);
                break;
            case (3):
                // bishop test
                boardState[36] = Piece(0, 3);
                break;
            case (4):
                // rook test
                boardState[36] = Piece(0, 4);
                break;
            case (5):
                // queen test
                boardState[36] = Piece(0, 5);
                //boardState[35] = Piece(1, 1);
                break;
            case (6):
                // king test
                boardState[36] = Piece(0, 6);
                boardState[32] = Piece(0, 4);
                boardState[39] = Piece(0, 4);
                break;
            case (7):
                // any other wacky board combo you want
                break;

        }
    }

    std::string display()
    {
        // string representation of the board for the pre front end stage

        std::string s;
        for (int ii = 0; ii < 17; ii++)
        {
            if (!(ii%2))
            {
                s += "  -----------------------------------------\n";
            }
            else
            {
                s += std::to_string(8-(ii/2)) + " |";
                for (int jj = 0; jj < 8; jj++)
                {
                    s += " " + boardState[(8 * (ii/2)) + jj].display() + " |";
                }
                s += "\n";
            }
        }
        s += "    A    B    C    D    E    F    G    H\n";
        return s;
    }

    std::string moveDisplay(int currentKey)
    {
        // string representation of an input piece's valid moves

        std::string s;
        std::vector<int> vMoves = verifyMoves(currentKey);
        if (vMoves.empty())
        {
            return "No Valid Moves";
        }
        for (int ii = 0; ii < 17; ii++)
        {
            if (!(ii%2))
            {
                s += "  -----------------------------------------\n";
            }
            else
            {
                s += std::to_string(8-(ii/2)) + " |";
                for (int jj = 0; jj < 8; jj++)
                {
                    s += " ";
                    for (int kk = 0; kk < vMoves.size(); kk++)
                    {
                        if (vMoves[kk] == ((8 * (ii / 2)) + jj))
                        {
                            s += "XX";
                            break;
                        }
                        else if (kk + 1 == vMoves.size())
                        {
                            s += "  ";
                        }
                    }
                    s += +" |";
                }
                s += "\n";
            }
        }
        s += "    A    B    C    D    E    F    G    H\n";
        return s;
    }

    std::vector<int> verifyMoves(int currentKey)
    {
        // iterates through every possible move, checking against the general rules and then piece specific rules to validate or discard moves
        // input currentKey: integer corresponding to the piece you are trying to move

        std::vector<int> gottenMoves = boardState[currentKey].getMoves();
        // retrieves list of every possible move difference
        std::vector<int> possibleMoves, verifiedMoves;
        for (int gottenMove : gottenMoves)
        {
            possibleMoves.push_back(gottenMove+currentKey);
            // creates new list of destination positions "possible moves"
        }
        bool prevMoveValid = true;
        // previous move test: if the previous move didn't work, then this move won't work (suitable mostly for b, r, and q)
        bool prevMoveCapture = false;
        for (int ii = 0; ii < possibleMoves.size(); ii++)
        {
            if (ii % 7 == 0)
            // taking advantage of the structure of the possible moves list, a piece can only possibly move 7 spaces in any direction
            // if it reaches that seventh move and restarts the search in a different direction, it won't eliminate moves based on the
            // previous move test.
            {
                prevMoveCapture = false;
                prevMoveValid = true;
            }
            int horizontalOffset = (gottenMoves[ii] % 8);
            // horizontal offset that the move being tested would incur
            int verticalOffset = (gottenMoves[ii] / 8);
            // horizontal offset that the move being tested would incur
            int horizontalPos = (possibleMoves[ii] % 8);
            // horizontal position of the move destination being tested
            int verticalPos = (possibleMoves[ii] / 8);
            // vertical position of the move destination being tested
            int currentHorizontalPos = (currentKey % 8);
            // horizontal position of the current piece's horizontal position
            int currentVerticalPos = (currentKey / 8);
            // vertical position of the current piece's vertical position
            Piece atTarget = boardState[possibleMoves[ii]];
            // copy of the piece that is at the target (for efficiency)
            if (boardState[currentKey].getColor() != turn)
            {
                continue;
            }
            if (possibleMoves[ii] > 63 or possibleMoves[ii] < 0)
                // checking to see if it is in range of the board
            {
                prevMoveValid = false;
                continue;
            }
            if (atTarget.exists() and (atTarget.getColor() == turn))
                // checking if the move in question lands on one of your own pieces
            {
                prevMoveValid = false;
                continue;
            }
            switch (boardState[currentKey].getId())
            // piece specific checks
            {
                case 1:
                    // pawn checks
                    if (!prevMoveValid and ii < 2)
                    {
                        continue;
                    }
                    if (horizontalOffset==0 and boardState[possibleMoves[ii]].exists() and (boardState[possibleMoves[ii]].getColor() != turn))
                        // checking directly ahead (cant capture forward)
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if (((verticalPos) == (currentVerticalPos)) or ((horizontalPos != currentHorizontalPos) and (abs(possibleMoves[ii] / 8 - (currentKey / 8)) > 1)))
                        // preventing wrap around illegal moves
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if (((abs(gottenMoves[ii]) / 8) > 1) and (boardState[currentKey].getMoveCount() > 0))
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if (horizontalOffset!=0 and !boardState[possibleMoves[ii]].exists())
                        // checking if there is a piece
                    {
                        bool cond1 = boardState[possibleMoves[ii]+((!turn)?8:-8)].getId() == 1;
                        // checks to make sure square adjacent is a pawn
                        bool cond2 = boardState[possibleMoves[ii]+((!turn)?8:-8)].getMoveCount() == 1;
                        // checks to make sure said pawn has only moved once
                        bool cond3 = ((verticalPos) == ((!turn)?2:5));
                        // checks if it is in the correct row
                        bool cond4 = possibleMoves[ii]+((!turn)?8:-8) == prevMoveKey;
                        // checks to make sure it was the pawn that may be en passantable that was the last piece to move
                        if (cond1 and cond2 and cond3 and cond4)
                            // checking en passant
                        {
                            enPassantTest = possibleMoves[ii];
                            break;
                        }
                        else
                        {
                            prevMoveValid = false;
                            continue;
                        }
                    }
                    break;
                case 2:
                    // knight checks
                    if ((abs((verticalPos) - (currentVerticalPos)) + abs((horizontalPos - currentHorizontalPos))) != 3)
                        // checks if euclidean distance is 3
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    break;
                case 3:
                    // bishop checks
                    if (!prevMoveValid)
                        // previous move valid test
                    {
                        continue;
                    }
                    if (prevMoveCapture)
                    {
                        continue;
                    }
                    if ((abs((verticalPos) - (currentVerticalPos)) + abs((horizontalPos - currentHorizontalPos))) % 2 != 0)
                        // bishop logic checking if the euclidean distance is divisible by two, eliminating any wrapping
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    break;
                case 4:
                    // rook checks
                    if (!prevMoveValid)
                        // previous move valid test
                    {
                        continue;
                    }
                    if (prevMoveCapture)
                    {
                        continue;
                    }
                    if (((possibleMoves[ii] < (currentKey - currentHorizontalPos)) or (possibleMoves[ii] > (currentKey - currentHorizontalPos + 7))) and (currentHorizontalPos - horizontalPos != 0))
                        // rook logic checking horizontal movement (vertical movement is easily covered by range check in the beginning
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    break;
                case 5:
                    // queen checks
                    if (!prevMoveValid)
                        // previous move valid test
                    {
                        continue;
                    }
                    if (prevMoveCapture)
                    {
                        continue;
                    }
                    // queen logic is largely a combination of rook and bishop logic
                    if ((abs(gottenMoves[ii]) < 7) or (gottenMoves[ii] % 8 == 0))
                        // checking rook moves logic
                    {
                        if (((possibleMoves[ii] < (currentKey - currentHorizontalPos)) or (possibleMoves[ii] > (currentKey - currentHorizontalPos + 7))) and (currentHorizontalPos - horizontalPos != 0))
                        {
                            prevMoveValid = false;
                            continue;
                        }
                    }
                    else if (((gottenMoves[ii] % 7 == 0) and (abs(gottenMoves[ii]) > 7)) or (gottenMoves[ii] % 9 == 0))
                        // checking bishop moves logic
                    {
                        if ((abs((verticalPos) - (currentVerticalPos)) + abs((horizontalPos - currentHorizontalPos))) % 2 != 0)
                        {
                            prevMoveValid = false;
                            continue;
                        }
                    }
                    break;
                case 6:
                    // king checks
                    if (boardState[currentKey].getMoveCount() > 0 and (gottenMoves[ii] == -2 or gottenMoves[ii] == 2))
                        // if the king has moved, then it won't be able to castle
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if (gottenMoves[ii] == -2)
                        // testing castle long requirements (empty space between king and rook, rook hasn't moved)
                    {
                        castleLong = (!boardState[currentKey-1].exists() and !boardState[currentKey-2].exists() and !boardState[currentKey-3].exists() and (boardState[currentKey-4].getId() == 4) and (boardState[currentKey-4].getColor() == turn) and (boardState[currentKey-4].getMoveCount() == 0));
                    }
                    if (gottenMoves[ii] == 2)
                        // testing castle requirements (empty space between king and rook, rook hasn't moved)
                    {
                        castle = (!boardState[currentKey+1].exists() and !boardState[currentKey+2].exists() and (boardState[currentKey+3].getId() == 4) and (boardState[currentKey+3].getColor() == turn) and (boardState[currentKey+3].getMoveCount() == 0));
                    }
                    if (gottenMoves[ii] == -2 and !castleLong)
                        // if castle long is invalid, then it eliminates the move
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if (gottenMoves[ii] == 2 and !castle)
                        // if castle is invalid, then it eliminates the move
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    if ((abs((verticalPos) - (currentVerticalPos)) + abs((horizontalPos - currentHorizontalPos))) > 2)
                        // invalidates move if euclidean distance is more than 2
                    {
                        prevMoveValid = false;
                        continue;
                    }
                    break;
            }
            // if it makes it through every check without entering a fail condition, it gets added to the list of verified moves
            prevMoveValid = true;
            verifiedMoves.push_back(possibleMoves[ii]);
            if (boardState[possibleMoves[ii]].getColor() == !turn and boardState[possibleMoves[ii]].exists())
            {
                prevMoveCapture = true;
            }
        }
        return verifiedMoves;
    }

    bool verifyMoveTarget(int currentKey, int targetKey)
    {
        // calls the verifyMove function before executing a move command
        // input currentKey: integer corresponding to the piece you are trying to move
        // input targetKey: integer corresponding to the pieces intended destination

        std::vector<int> moves = verifyMoves(currentKey);
        if (moves.empty() or (boardState[currentKey].getColor() != turn))
            // if its not your turn, or if the selected piece has no valid moves, it fails
        {
            std::cout << "invalid move!\n";
            std::cout << display();
            return false;
        }
        for (int move : moves)
        {
            if (move == targetKey)
                // checks if any of the moves match with the inputted target
            {
                std::cout << "\ncurrentKey: " << currentKey << "\ntargetKey: " << targetKey << "\n\n";
                return makeMove(currentKey, targetKey);
            }
        }
        //std::cout << "invalid move!\n";
        //std::cout << display();
        // catch all if the move is invalid
    }

    bool makeMove(int currentKey, int targetKey, bool probabilityOverride = 0, bool success = 1)
    // executes a move regardless of whether it is verified or not
    // input currentKey: integer corresponding to the piece you are trying to move
    // input targetKey: integer corresponding to the pieces intended destination
    // inputs probabilityOverride and success: bools that allow specification of
    // success or failure for ai state generation

    {
        bool successVal = true;
        if (boardState[targetKey].exists() or enPassantTest == targetKey)
            // already ruled out pieces of same color, so if it exists, it's capturable
        {
            if (probabilityOverride?success:chance(currentKey))
            {
                dead.push_back(boardState[targetKey]);
                // add to killed list
                if (boardState[targetKey].getId() == 6)
                    // if the king dies, the game ends
                {
                    gameOver = true;
                }
                if (enPassantTest == targetKey)
                    // executes en passant if the target move is en passant-able
                {
                    dead.push_back(boardState[targetKey + ((!turn) ? 8 : -8)]);
                    boardState[targetKey + ((!turn) ? 8 : -8)] = Piece();
                    enPassantTest = 64;
                }
                /*if (boardState[currentKey].getId() == 1 and (targetKey / 8 == (!turn?0:7)))
                    // executes promotion if target move is promote-able
                {
                    promotion(boardState[currentKey]);
                }*/

                // remaining logic for making moves / captures
                prevMoveKey = targetKey;
                boardState[currentKey].incMoveCount();
                boardState[targetKey] = boardState[currentKey];
                boardState[currentKey] = Piece();
                ((!turn)?whiteProbability:blackProbability) = 10;
            }
            else
            {
                if (((!turn)?whiteProbability:blackProbability) > 100)
                {
                    ((!turn)?whiteProbability:blackProbability) = 100;
                }
                ((!turn)?whiteProbability:blackProbability) /= 2;
                successVal = false;
            }
        }

        if (!boardState[targetKey].exists() and enPassantTest != targetKey)
        {
            if (castleLong and targetKey == (currentKey - 2))
                // executes castling long if target move is castle long-able
            {
                boardState[targetKey + 1] = boardState[targetKey - 2];
                boardState[targetKey - 2] = Piece();
                castleLong = false;
            }
            if (castle and targetKey == (currentKey + 2))
                // executes castling if target move is castle-able
            {
                boardState[targetKey - 1] = boardState[targetKey + 1];
                boardState[targetKey + 1] = Piece();
                castle = false;
            }
            /*if (boardState[currentKey].getId() == 1 and (targetKey / 8 == (!turn ? 0 : 7)))
                // executes promotion if target move is promote-able
            {
                promotion(boardState[currentKey]);
            }*/

            int modifier = 10;

            if (((!turn)?whitePiecesRem:blackPiecesRem) < 9)
            {
                modifier *= 2;
            }

            if (coinFlipActive)
            {
                if (coinFlip())
                {
                    modifier *= 2;
                }
                else
                {
                    modifier *= 0;
                }
            }

            ((!turn)?whiteProbability:blackProbability) += modifier;
            if ((!turn)?whiteProbability:blackProbability > 100)
            {
                ((!turn)?whiteProbability:blackProbability) = 100;
            }
            // remaining logic for making moves / captures
            prevMoveKey = targetKey;
            boardState[currentKey].incMoveCount();
            boardState[targetKey] = boardState[currentKey];
            boardState[currentKey] = Piece();
        }
        if (!mode)
        {
            turn = !turn;
        }
        //std::cout << display();
        //std::cout << "\nWhite Prob: " << whiteProbability << "\nBlack Prob: " << blackProbability << "\n";
        return successVal;
    }

    void promotion(int key, int selection)
    // method that promotes a piece
    // input &p: Piece object reference to be changed
    {
        boardState[key].setId(selection);
    }

    bool chance(int currentKey)
    // chance method that changes this from chess to probability chess by deciding the chance a capture is realized
    // input currentKey: integer corresponding to the piece you are trying to make a capture with
    {
        srand(time(nullptr));
        int likelihood = ((!turn)?whiteProbability:blackProbability);
        int id = boardState[currentKey].getId();
        switch (id)
        // list of probability modifiers corresponding to each piece.
        {
            case 1:
                likelihood += 10;
                break;
            case 2: case 3:
                likelihood += 20;
                break;
            case 4:
                likelihood += 30;
                break;
            case 5:
                likelihood += 60;
                break;
            case 6:
                likelihood += 80;
                break;
            default:
                break;
        }
        int tester = (rand() % 100);
        if (tester < likelihood)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool coinFlip()
    // code that just returns 50/50 true or false
    {
        srand(time(nullptr));
        int tester = (rand() % 2);
        return (tester != 0);
    }

    void toggleCoinFlip()
    {
        coinFlipActive = !coinFlipActive;
    }

    std::map<int,std::pair<int,std::vector<int>>> generateAllMoves()
    // generates every possible move that could be made
    {
        numPossibleMoves = 0;
        std::map<int,std::pair<int,std::vector<int>>> outp;
        std::vector<int> pieceKeys;
        for (int ii = 0; ii < 64; ii++)
        {
            if (boardState[ii].exists() and boardState[ii].getColor() == turn)
            {
                pieceKeys.push_back(ii);
            }
        }
        int trueIndex = 0;
        for (int index = 0; index < pieceKeys.size(); index++)
        {
            std::vector<int> moves = verifyMoves(pieceKeys[index]);
            if (moves.size() > 0)
            {
                outp[trueIndex] = std::make_pair(pieceKeys[index], moves);
                numPossibleMoves += moves.size();
                trueIndex++;
            }
        }
        return outp;
    }

    double getPieceScore()
    {
        // ok im spaghettifying this code DONT FORGET TO CHECK TURN ON GAME OVER WHEN I GET TO THE LAB
        if (gameOver)
        {
            return -std::numeric_limits<double>::infinity();
        }
        int score = 0;
        for (int ii = 0; ii < 64; ii++)
        {
            int val;
            switch (boardState[ii].getId())
            {
                default:
                    val = 0;
                    break;
                case 1:
                    val = 1;
                    break;
                case 2:
                    val = 3;
                    break;
                case 3:
                    val = 3;
                    break;
                case 4:
                    val = 5;
                    break;
                case 5:
                    val = 9;
                    break;
            }
            score += (val * ((boardState[ii].getColor()^turn)?-1:1));
        }
        return score;
    }

    void reset()
    {
        for (int ii = 0; ii < 64; ii++)
        {
            boardState[ii] = Piece();
        }
        boardState[0] = Piece(1, 4);
        boardState[1] = Piece(1, 2);
        boardState[2] = Piece(1, 3);
        boardState[3] = Piece(1, 5);
        boardState[4] = Piece(1, 6);
        boardState[5] = Piece(1, 3);
        boardState[6] = Piece(1, 2);
        boardState[7] = Piece(1, 4);
        boardState[8] = Piece(1, 1);
        boardState[9] = Piece(1, 1);
        boardState[10] = Piece(1, 1);
        boardState[11] = Piece(1, 1);
        boardState[12] = Piece(1, 1);
        boardState[13] = Piece(1, 1);
        boardState[14] = Piece(1, 1);
        boardState[15] = Piece(1, 1);
        boardState[48] = Piece(0, 1);
        boardState[49] = Piece(0, 1);
        boardState[50] = Piece(0, 1);
        boardState[51] = Piece(0, 1);
        boardState[52] = Piece(0, 1);
        boardState[53] = Piece(0, 1);
        boardState[54] = Piece(0, 1);
        boardState[55] = Piece(0, 1);
        boardState[56] = Piece(0, 4);
        boardState[57] = Piece(0, 2);
        boardState[58] = Piece(0, 3);
        boardState[59] = Piece(0, 5);
        boardState[60] = Piece(0, 6);
        boardState[61] = Piece(0, 3);
        boardState[62] = Piece(0, 2);
        boardState[63] = Piece(0, 4);
        turn = 0;
        gameOver = false;
        castle = false;
        castleLong = false;
        coinFlipActive = false;
        prevMoveKey = -1;
        enPassantTest = -1;
        whiteMoves = 0;
        blackMoves = 0;
        whiteProbability = 10;
        blackProbability = 10;
        whitePiecesRem = 16;
        blackPiecesRem = 16;
        numPossibleMoves = 0;
        dead.clear();
    }

    std::map<int,Piece> boardState;
    // the map holding the current state of the board

    std::vector<Piece> dead;
    // list of pieces that have been captured

    bool turn, gameOver = false;
    // turn 0: white to move
    // turn 1: black to move
    // gameOver 0: game not over
    // gameOver 1: game over

    bool castle = false, castleLong = false;
    // board state booleans allowing a proposed move to castle or not

    bool coinFlipActive = false;
    // boolean corresponding to an unimplemented function that asks the player if they want to coin flip

    int mode;
    // the board setup

    int prevMoveKey = -1, enPassantTest = -1;
    // en passant helping int fields

    int whiteMoves = 0, blackMoves = 0;
    // integers corresponding to the total number of moves played for each side

    int whiteProbability = 10, blackProbability = 10;
    // integers corresponding to the probability pool for each side

    int whitePiecesRem = 16, blackPiecesRem = 16;
    // integers corresponding to the number of pieces remaining on each side

    int numPossibleMoves = 0;

protected:

};
#endif //PROBABILITYCHESS_BOARD_H
