#include <iostream>
#include <vector>
using namespace std;

int isvalid(char k, vector<vector<char> > A, int i, int j) { //Checking if putting the current element is not in same row, column or box
    for(int t = 0; t < 9; t++) {
        if(A[t][j] == k) //Checking jth column
            return 0;
        if(A[i][t] == k) //Checking ith row
            return 0;
        if(A[(i/3)*3+t/3][(j/3)*3+t%3] == k) //Checking current box
            return 0;
    }
    return 1;
}

bool sudoku(vector<vector<char> > &A, int i, int j) {

    if(i > 8 || j > 8) //If coordinates of the matrix goes out of bounds return true
        return true;

    if(A[i][j] == '.') {
        for(char k = '1'; k <= '9'; k++) { //Trying to put every character possible
            if(isvalid(k, A, i, j)) { //If putting character `k` doesn't makes the sudoku invaild put it
                A[i][j] = k;
                if(sudoku(A, (i+1)%9, j+(i+1)/9))// CHANGE ONE
                    return true;
                else
                    A[i][j] = '.'; //Reset(If the sudoku can't be solved with putting `k` in `i, j` th index replace the '.' character at that position)
            }
        }
    }

    else {
        if(sudoku(A, (i+1)%9, j+(i+1)/9)) // CHANGE TWO
            return true;
    }
    return false;//This should trigger backtracking
}

void solveSudoku(vector<vector<char> > &A) {
    sudoku(A, 0, 0);
}

int main() {
    vector<vector<char> > A = {{'5','3','.','.','7','.','.','.','.'}, {'6','.','.','1','9','5','.','.','.'}, {'.','9','8','.','.','.','.','6','.'},
                               {'8','.','.','.','6','.','.','.','3'}, {'4','.','.','8','.','3','.','.','1'}, {'7','.','.','.','2','.','.','.','6'},
                               {'.','6','.','.','.','.','2','8','.'}, {'.','.','.','4','1','9','.','.','5'}, {'.','.','.','.','8','.','.','7','9'}}; //Input sudoku
    solveSudoku(A);
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout<<A[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

/*#include <iostream>
#include <vector>
#include <ostream>

using namespace std;

struct sb
{
    char board[9][9];

    sb(const vector<string> &ss)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = ss[i][j];
            }
        }
    }

    friend ostream &operator<<(ostream &os, const sb &s)
    {
        for (auto i = 0; i < 9; i++)
        {
            for (auto j = 0; j < 9; i++)
            {
                os << s[i][j];
            }
            os << "\n";
        }

        return os;
    }
};

struct ss
{
    sb s0;

    vector<sb> solve()
    {
        vector<sb> r;

        r.push_back(s0);
        solve(s0, r);

        return r;
    }

    void solve(const sb &s, vector<sb> &r)
    {
        pair<int, int> np = s.get_next_pos();

        for (int i = 1; i <= 9; i++)
        {
            bool eval = s.test(np, i);
            if (eval)
                solve(s.set(np, i), r);
        }
    }
};

int main()
{
    ss x
    {
        vector<string>
        {
            "4..3.....",
            "19.87.4..",
            "..7..29..",
            ".8.9..7.5",
            "..5......",
            ".73..1.64",
            "...1..3.9",
            "71.....4.",
            "..97.4..2"
        }
    };

    auto r = x.solve();

    for (auto &i : r)
        cout << i << "\n\n";

    return 0;
}*/
