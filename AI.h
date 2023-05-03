//
// Created by haven on 4/19/23.
//

#ifndef GROUP8PROJECT_AI_H
#define GROUP8PROJECT_AI_H

#include "State.h"
#include <algorithm>

class AI
{
public:
    AI(State inpState, int inpMode = 0, int inpDepthLimit = 1): currentState(inpState), mode(inpMode), depthLimit(inpDepthLimit) {}

    std::pair<int,int> pickMove()
    {
        switch (mode)
        {
            case 0:
                return randomMove();
            case 1:
                return calculatedMove();
            default:
                return std::make_pair(-1, -1);
        }
    }

    std::pair<int,int> randomMove()
    {
        // picks a random piece that has valid moves, then randomly selects a move that piece can make
        srand(time(NULL));
        std::map <int, std::pair <int, std::vector <int> > > moves = currentState.currentBoard.generateAllMoves();
        int currentKey = 0, targetKey = 0;
        int mSize = moves.size();
        int indexOne = (rand() % mSize);
        currentKey = moves[indexOne].first;
        int cmSize = moves[indexOne].second.size();
        int indexTwo = (rand() % cmSize);
        targetKey = moves[indexOne].second[indexTwo];
        std::pair<int,int> move (currentKey, targetKey);
        return move;
    }

    std::pair<int,int> calculatedMove()
    {
        // uses the score generated to pick the "best" next move
        std::vector<State> states = currentState.generateStates();
        int maxIndex = 0;
        int maxScore = 0;
        for (int ii = 0; ii < states.size(); ii++)
        {
             int score = generateScore(states[ii], depthLimit-1);
             if (score > maxScore)
             {
                 maxScore = score;
                 maxIndex = ii;
             }
             std::cout << "\ncurrentKey: " << states[ii].moveMade.first << "\ntargetKey: " << states[ii].moveMade.second << "\nscore: " << score << "\n\n";
        }
        return states[maxIndex].moveMade;
    }

    double boardScore(State s)
    // this function would, if i had the time, do more than just call the getPieceScore() method
    // such as analyzing piece locations and whatnot
    {
        return s.currentBoard.getPieceScore();
    }

    double generateScore(State s, int depth)
    // recursively generates a score based on the moves it could make in the future
    // input s: State object to be analyzed
    // input depth: int that corresponds to the depth limit
    {
        if (depth == 0)
        {
            double score = this->boardScore(currentState);
            std::cout << "\nin: generateScore() score: " << score << "\n\n";
            return score;
        }
        else
        {
            std::vector<State> states = s.generateStates();
            std::vector<double> scores;
            for (int ii = 0; ii < states.size(); ii++)
            {
                scores.push_back(generateScore(states[ii], (depth - 1)));
            }
            return -*std::max_element(scores.begin(), scores.end());
        }
    }
    int mode, depthLimit;
    // if i had made more ai's, this would be more prevalent, but it just corresponds to either random or calculated

    State currentState;
    // State object that it uses to generate the next move
};

#endif //GROUP8PROJECT_AI_H
