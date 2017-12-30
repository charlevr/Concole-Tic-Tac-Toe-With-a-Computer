#include <iostream>
#include <vector>
using namespace std;

class GameState
{
    private:
        vector <vector<char> > board;
        bool turn;
    public:
        GameState();
        void makeMove(int x, int y);
        bool checkWinner();
        void printBoard();
        bool checkFull();
        vector <vector<char> > getBoard();
};