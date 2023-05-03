//
// Created by haven on 4/14/23.
//

#ifndef PROBABILITYCHESS_STATE_H
#define PROBABILITYCHESS_STATE_H

#include <utility>

#include "Board.h"

class State
{
public:
    State(Board b, State* pred, std::pair<int,int> inpMove): currentBoard(std::move(b)), pPredecessor(pred), score(0), moveMade(inpMove){}

    std::vector<State> generateStates()
    // generates every possible move that could be made into a new state
    {
        std::vector<State> outp;
        if (currentBoard.gameOver)
        {
            return outp;
        }

        std::map<int,std::pair<int,std::vector<int>>> moves = currentBoard.generateAllMoves();
        for (int ii = 0; ii < moves.size(); ii++)
        {
            for (int jj = 0; jj < moves[ii].second.size(); jj++)
            {
                Board nextBoard = currentBoard;
                nextBoard.makeMove(moves[ii].first, moves[ii].second[jj], 1, 1);
                currentBoard.display();
                nextBoard.display();
                outp.push_back(*new State(nextBoard, this, std::make_pair(moves[ii].first, moves[ii].second[jj])));
            }
        }
        return outp;
    };

    double score;
    std::pair<int,int> moveMade;
    Board currentBoard;
    State* pPredecessor;
    std::vector<State> possibleStates;
};

#endif //PROBABILITYCHESS_STATE_H
