#include <iostream>

#include "AI.h"

int interpretMove(std::string inp)
{
    int value = 0;
    value += (int) (inp[0] - 'A');
    value += 8 * (7 - (int) (inp[1] - '1'));
    return value;
}

int main()
{
    int mode;
    std::cout << "Select Mode: Two Player (0) or One Player vs AI (1)\n";
    std:: cin >> mode;
    Board board = Board(5); // set parameter 1-6 for test boards of each piece, leave blank for standard board
    std::cout << board.display();
    while (!board.gameOver)
    {
        std::cout << board.getPieceScore() << "\n";
        int currentInt, targetInt;
        if (mode and board.turn)
        {
            State currentState = *new State(board, nullptr, std::make_pair(-1, -1));
            AI playerTwo = AI(currentState, 1);
            std::pair<int,int> move = playerTwo.pickMove();
            currentInt = move.first;
            targetInt = move.second;
        }
        else
        {
            std::string current, target;
            std::cout << (board.turn?"Black":"White") << "'s turn to move. Select piece to move (form: XN)\n";
            std::cin >> current;
            std::cout << board.moveDisplay(interpretMove(current)) << "Select destination\n";
            std::cin >> target;
            currentInt = interpretMove(current);
            targetInt = interpretMove(target);
        }
        board.verifyMoveTarget(currentInt, targetInt);
        std::cout << board.display();
        std::cout << "\nWhite Prob: " << board.whiteProbability << "\nBlack Prob: " << board.blackProbability << "\n";
    }
    std::cout << board.getPieceScore() << "\n";
    std::cout << (!board.turn?"Black":"White") << " Wins!\n";
}