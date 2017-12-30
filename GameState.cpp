#include <iostream>
#include "GameState.h"
using namespace std;

/*
    Constructor for the GameState class. Sets the board
    to all '.' characters initially so that any move can be
    made. Sets 'turn' to true; in this case 'true' == 'X' and
    'false' == 'O'.
*/
GameState::GameState()
{
    board.push_back(vector<char>(3, '.'));
    board.push_back(vector<char>(3, '.'));
    board.push_back(vector<char>(3, '.'));
    turn = true;
}


/*
    Prints the board class's current board mark by mark
*/
void GameState::printBoard()
{
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            cout << board[row][col] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

/*
    Check's the class's board to see if a winner exists.
    @return true is there is a winner and false otherwise
*/
bool GameState::checkWinner()
{
    //Checks each row
    for(int row = 0; row < 3; row++)
    {
        //If the first element of a row is equal to the second and third elements, there is a winner. 
        if((board[row][0] == board[row][1]) && (board[row][0] == board[row][2]) && (board[row][0] != '.'))
        {
            return true;
        }
    }
    //Checks each column
    for(int col = 0;  col < 3; col++)
    {
        //If the first element of one colummn is equal to the second and third elements, there is a winner. 
        if((board[0][col] == board[1][col]) && (board[0][col] == board[2][col]) && (board[0][col] != '.'))
        {
            return true;
        }
    }
    //Check L-R diagonal; same as the row and column except checks the [0][0] to [1][1] and [2][2]
    if((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] != '.'))
    {
        return true;
    }
    //Check R-L diagonal; same as rest except checks [2][0] to [1][1] and [0][2]
    if((board[2][0] == board[1][1]) && (board[2][0] == board[0][2]) && (board[2][0] != '.'))
    {
        return true;
    }
    
    //If none of the conditions are true, then there is no winner. 
    return false;
}

/*
    Checks if the board is full.
    @return true or false depending on if the board is full.
*/
bool GameState::checkFull()
{
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            if(board[row][col] == '.')
            {
                return false;
            }
        }
    }
    return true;
}

/*
    Checks if a move is valid then makes the move on the board. After the move 
    is made, the turn is switched to the other mark. 
*/
void GameState::makeMove(int x, int y)
{
    if((x > 3) ||(y > 3))
    {
        cout << "Your number is too high\n";
    }
    else if((x < 0) ||(y < 0))
    {
        cout << "Your number is too low.\n";
    }
    else if(board[x][y] != '.')
    {
        cout <<"There is already something here.\n";
    }
    else
    {
        if(turn)
        {
            board[x][y] = 'X';
        }
        else
        {
            board[x][y] = 'O';
        }
        turn = !turn;
    }
}

/*
    Returns the board. 
*/
vector <vector<char> > GameState::getBoard()
{
    return board;
}
