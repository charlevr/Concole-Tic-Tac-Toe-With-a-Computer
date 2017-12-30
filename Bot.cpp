#include <iostream>
#include <vector>
#include <cstdlib>
#include "Bot.h"
using namespace std;

/*
    Constructor for the Bot class which accepts a bool that determines if
    it is X or O.
    @param start, boolean that tells bot what turn they are
*/
Bot::Bot(bool start)
{
    //If false, then the bot must be going first and is therefore X
    if(!start)
    {
        mark = 'X';
        oppMark = 'O';
    }
    //If true, the opposite is true.
    else
    {
        mark = 'O';
        oppMark = 'X';
    }
}

/*
    If the bot is going first, always put an X in the middle.
    Implemented for simplicity since the middle will always be the best starting spot. 
    @return vector<int>, a point or spot on the board (1,1).
*/
vector<int> Bot::ifFirst(const vector <vector<char> > &board)
{
    vector<int> point;
    point.push_back(1);
    point.push_back(1);
    return point;
}

/*
    Counts the number of X's and O's on the board. Used to 
    keep track of game progress. 
    @param const vector <vector<char> > &board, a reference to a 2d array which is the board. 
    @return int, the number of marks on a board. 
*/
int Bot::countMarks(const vector <vector<char> > &board)
{
    int count = 0;
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            if((board[row][col] == 'X') || (board[row][col] == 'O'))
            {
                count++;
            }
        }
    }
    return count;
}

/*
    Finds  where an O is on the board. Used in the early stage of the game
    to decide where to put an X on the board if the AI goes first. 
    @param const vector <vector<char> > &board, reference to the board
    @return vector <vector<int> >, a vector of points that O is present in. 
*/
vector <vector<int> > Bot::find(const vector <vector<char> > &board, char currMark)
{
    vector <vector<int> > oVec;
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            if((board[row][col] == currMark))
            {
                vector<int> m;
                m.push_back(row);
                m.push_back(col);
                oVec.push_back(m);
            }
        }
    }   
    return oVec;
}

/*
    Makes the second move for X depending on if the O is on an
    edge or a corner. 
    @param const vector <vector<char> > &board, reference to the current board. 
    @return vector <int>, the row and column of the move
*/
vector <int> Bot::X(const vector <vector<char> > &board)
{
        vector <vector<int> > points = find(board, oppMark); //Finds where the 'O' is
        vector<int> move;
        //checks for corners
        //If corner, put an X on the opposite corner.
        if((board[0][0] == 'O')|| (board[0][2] == 'O') || (board[2][0] == 'O') || (board[2][2] == 'O'))
        {
            if(points[0][0] == 0)
            {
                move.push_back(2);
            }
            else
            {
                move.push_back(0);
            }
            
            if(points[0][1] == 0)
            {
                move.push_back(2);
            }
            else
            {
                move.push_back(0);
            }
            return move;
        }
        //Checks for edges
        //If on the edge, put on the corner on the side of the edge. 
        else if((board[0][1] == 'O')|| (board[1][0] == 'O') || (board[2][1] == 'O') || (board[1][2] == 'O'))
        {
            if((points[0][0] == 0) || (points[0][1] == 0))
            {
                move.push_back(0);
                move.push_back(0);
                return move;
            }
            else if((points[0][0] == 2) || (points[0][1] == 2))
            {
                move.push_back(2);
                move.push_back(2);  
                return move;
            }
        }
    
}

/*
    Special strategy for if the ai is 'O'; Takes the middle or a corner. 
    @param &board, 2d vector represnting the board
    @return vecctor<int> the row and column of the move. 
*/
vector <int> Bot::O(const vector <vector<char> > &board)
{
    vector <vector<int> > points = find(board, oppMark); //Finds where the 'X' is
    vector<int> move;
    
    if((board[0][0] == 'X')|| (board[0][2] == 'X') || (board[2][0] == 'X') || (board[2][2] == 'X'))
    {
        move.push_back(1);
        move.push_back(1);
        return move;
    }
    else 
    {
        vector<int> corner = takeCorner(board, mark);
        move.push_back(corner[0]);
        move.push_back(corner[1]);
        return move;
    }
}

/*
    Identical to the checkWinner function in the GameState class. 
    @param &board, reference to a 2d vector representing the board
    @return bool, true of there is a winner and false otherwise. 
*/
bool Bot::isWin(const vector <vector<char> > &board)
{
    for(int row = 0; row < 3; row++)
    {
        if((board[row][0] == board[row][1]) && (board[row][0] == board[row][2]) && (board[row][0] != '.'))
        {
            return true;
        }
    }
    for(int col = 0;  col < 3; col++)
    {
        if((board[0][col] == board[1][col]) && (board[0][col] == board[2][col]) && (board[0][col] != '.'))
        {
            return true;
        }
    }
    if((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] != '.'))
    {
        return true;
    }
    if((board[2][0] == board[1][1]) && (board[2][0] == board[0][2]) && (board[2][0] != '.'))
    {
        return true;
    }
    return false;
}

/*
    Finds a winning move for the given mark.
    @param &board, reference to a 2d vector representing the board
    @param currMark, mark we want to find a winning move for.
    @return vector<int>, row ad column of where we want to put the mark. 
*/
vector<int> Bot::findWinningMove(const vector <vector<char> > &board, char currMark)
{
    vector <vector<char> > *copy = new vector <vector<char> >(); //Allocates new memory for a copy of the board
    vector <vector<char> > &rCopy = *copy; //creates a reference to the copy
    for(int i = 0; i < board.size(); i++)
    {
        copy->push_back(board[i]); //Copies the actual board
    }
    vector<int> move; //Initialize the move
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            //If an entry is empty, test it
            if(rCopy[i][j] == '.')
            {
                rCopy[i][j] = currMark; //Put mark on the copy
                //If the mark wins, return the row and column
                if(isWin(rCopy))
                {
                    move.push_back(i);
                    move.push_back(j);
                    return move;
                }
                //Otherwise, remove the mark and make the entry empty again. 
                else
                {
                    rCopy[i][j] = '.';
                }
            }
        }
    }
    //If there is no winning move, push -1 into the vector
    move.push_back(-1);
    delete copy; //Deallocate the memory
    return move; //return the move
}

/*
    Takes a corner if there are no other possible mvoes left. 
    @param &board, 2d vector representing the board
    @param currMark, the mark we want to mark a corner for. 
    @return vector <int> row and col of the corner. 
*/
vector<int> Bot::takeCorner(const vector <vector<char> > &board, char currMark)
{
    vector <vector<char> > *copy2 = new vector <vector<char> >(); 
    vector <vector<char> > &rCopy2 = *copy2;
    
    vector<int> move;
    
    for(int i = 0; i < board.size(); i++)
    {
        copy2->push_back(board[i]); //Copies the actual board
    }
    if(rCopy2[0][0] == '.')
    {
        move.push_back(0);
        move.push_back(0);
    }
    else if(rCopy2[0][2] == '.')
    {
        move.push_back(0);
        move.push_back(2);
    }
    else if(rCopy2[2][0] == '.')
    {
        move.push_back(2);
        move.push_back(0);
    }
    else if(rCopy2[2][2] == '.')
    {
        move.push_back(2);
        move.push_back(2);
    }
    else
    {
        move.push_back(-1);
        move.push_back(-1);
    }
    delete copy2;
    return move;
}

/*
    Creates a random move for the bot if there are no winning or blocking moves. 
    @param &board, reference to a 2d vector that represents the board
    @return vector<int>, row and column of the random move. 
*/
vector<int> Bot::randMove(const vector <vector<char> > &board)
{
    vector <vector<char> > *c = new vector <vector<char> >();
    vector <vector<char> > &rC= *c;
    for(int i = 0; i < board.size(); i++)
    {
        c->push_back(board[i]);
    }
    
    //Initialize potential points
    int randX;
    int randY;
    
    vector<int> move;
    
    while(true)
    {
        randX = rand()%3; //Random numbers from 0-2 that will be random points
        randY = rand()%3;
        //If the spot is empty, fill it with the mark, otherwise loop back and make another random move. 
        if(rC[randX][randY] == '.')
        {
            rC[randX][randY] = mark;
            move.push_back(randX);
            move.push_back(randY);
            delete c;
            return move;
        }
    }
}

/*
    Composes all of the techniques into one function; analuzes the board
    and determins where to put the mark. 
    @param &board, 2d vector that represents the board
*/
vector<int> Bot::analyze(const vector <vector<char> > &board)
{
    //Special strategy if the bot is X and is in the early stage of the game. 
    if(mark == 'X')
    {
        if(countMarks(board) == 2)
        {
            vector<int> p = X(board); //Get a the point
            vector<int> move; //Push into move and return it. 
            move.push_back(p[0]);
            move.push_back(p[1]);
            return move;
        }
    }
    else
    {
        //The second move for 'O'
        if(countMarks(board) == 1)
        {
            vector<int> p = O(board); //Get a the point
            vector<int> move; //Push into move and return it. 
            move.push_back(p[0]);
            move.push_back(p[1]);
            return move;
        }
        //Prevents the trap where X is at 0,0 and 2,2 or 2,0 and 0,2. 
        else if(countMarks(board) == 3)
        {
            if(((board[0][0] == 'X') && (board[2][2] == 'X')) || ((board[2][0] == 'X') && (board[0][2] == 'X')))
            {
                vector<int> move;
                move.push_back(2);
                move.push_back(1);
                return move;
            }
        }
    }
    /*
        Initializes 3 vectors:
        p checks if there is a winner move for the ai
        o checks if there's a winning move for the human
        r creates a random move if neither of the above are true.
        
        The ai winning takes first priority. 
    */
    vector<int> p = findWinningMove(board, mark); //Checks for the ai's mark. 
    vector<int> o = findWinningMove(board, oppMark);//Checks for the human's mark. 
    vector<int> c = takeCorner(board, mark);
    vector<int> r = randMove(board);
    //If any return -1, then there is no winning move. 
    if(p[0] != -1)
    {
        vector<int> move;
        move.push_back(p[0]);
        move.push_back(p[1]);
        return move;
    }
    else if(o[0] != -1)
    {
        vector<int> move;
        move.push_back(o[0]);
        move.push_back(o[1]);
        return move;
    }
    else if(c[0] != -1)
    {
        vector<int> move;
        move.push_back(c[0]);
        move.push_back(c[1]);
        return move;
    }
    else
    {
        vector<int> move;
        move.push_back(r[0]);
        move.push_back(r[1]);
        return move;
    }
}