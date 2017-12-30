#include <iostream>
#include <cstdlib>
using namespace std;

class Bot
{
    private:
        char mark;
        char oppMark;
        vector<int> X(const vector <vector<char> > &board);
        vector<int> O(const vector <vector<char> > &board);
        int countMarks(const vector <vector<char> > &board);
        vector <vector<int> > find(const vector <vector<char> > &board, char currMark);
        vector<int> findWinningMove(const vector <vector<char> > &board, char currMark);
        vector<int> randMove(const vector <vector<char> > &board);
        vector<int> takeCorner(const vector <vector<char> > &board, char currMark);
        bool isWin(const vector <vector<char> > &board);
    public:
        Bot(bool start);
        vector<int> analyze(const vector <vector<char> > &board);
        vector<int> ifFirst(const vector <vector<char> > &board);
};