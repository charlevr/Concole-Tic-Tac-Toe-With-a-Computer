#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "GameState.h"
#include "Bot.h"
using namespace std;

/*
    Asks user if they want to go first or second.
    @return bool, true if they want to go first and false otherwise. 
*/
bool botFirstOrSecond()
{
    char c;
    while(true)
    {
        cout << "Press f if you want to go first or s if second: ";
        cin >> c;
        
        if((c != 'f') && (c != 's'))
        {
            cout << "Give me a valid input!\n";
        }
        else if(c == 'f')
        {
            return true;
        }
        else if (c == 's')
        {
            return false;
        }
    }
}

/*
    Checks teh validity of a move before it is made.
    @param x, y, row and column of the potential move
    @param &board, 2d vector representing the board
    @return bool, true if the moe is valid and false otherwise. 
*/
bool checkMove(int x, int y, const vector <vector<char> > &b)
{
    if((x > 3) ||(y > 3))
    {
        cout << "Your number is too high\n";
        return false;
    }
    else if((x < 0) ||(y < 0))
    {
        cout << "Your number is too low.\n";
        return false;
    }
    else if(b[x][y] != '.')
    {
        cout <<"There is already something here.\n";
        return false;
    }
    else
    {
        return true;
    }
}



int main()
{
    bool playerIsFirst = botFirstOrSecond(); //Check first if player wants to go first. 
    
    Bot *ai = new Bot(playerIsFirst); //Create a pointer to a new Bot object given if the player wants to go first or not
    GameState *game = new GameState(); //Create a points to a new GameState object with an empty board. 
    
    //If the player wants to go second, use the bot's special strategy for going first (i.e. put X in the middle).
    if(!playerIsFirst)
    {
        vector<int> points = ai->ifFirst(game->getBoard());
        game->makeMove(points[0], points[1]);
        game->printBoard();
    }
    else
    {
        game->printBoard();
    }
    
    
    //Game loops until a winner is found
    while(true)
    {
        int x;
        int y;
        
        //Keeps looping until the user enters a valid move
        while(true)
        {
            cout << "Enter an row (1-3) and column (1-3) value format: row column: \n";
            cin >> x;
            cin >> y;
            
            if(checkMove(x-1, y-1, game->getBoard()))
            {
                break;
            }
        }
        
        game->makeMove(x-1, y-1);
        game->printBoard();
        
        //Check for a winner after the user has gone. 
        if(game->checkWinner() || game->checkFull())
        {
            if(game->checkFull())
            {
                cout << "It is a tie!\n";
            }
            else
            {
                cout << "You have won! \n";
            }
            break;
        }
        
        cout << "AI's turn\n";
        vector<int> p = ai->analyze(game->getBoard()); //Make ai analyze the board and make a move. 
        game->makeMove(p[0], p[1]);
        game->printBoard();
        
        //Check for a winner after the ai has gone. 
        if(game->checkWinner() || game->checkFull())
        {
            if(game->checkFull())
            {
                cout << "It is a tie!\n";
            }
            else
            {
                cout << "The ai has won! \n";
            }
            break;
        }

    }
    return 0;
}