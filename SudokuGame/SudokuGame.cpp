#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;
    void show(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j]<<' ';
            }
            cout << endl;
        }
        cout << endl;
        cout << "Please enter g to get new game, s to solve, or e to exit."
             << endl;
    }
    bool dfs(vector<vector<char>>& board, int k, int rules[3][9][9]) {
        while (k < 81 && board[k/9][k%9] != '.') k++;
        if (k == 81) return 1;
        int i = k/9, j = k%9;
        for (int c = 0; c < 9; c++) {
            if (!rules[0][i][c] && !rules[1][j][c] && !rules[2][i/3*3+j/3][c]) {
                board[i][j] = '1'+c;
                rules[0][i][c] = rules[1][j][c] = rules[2][i/3*3+j/3][c] = 1;
                if (dfs(board, k+1, rules)) return 1;
                rules[0][i][c] = rules[1][j][c] = rules[2][i/3*3+j/3][c] = 0;
            }
        }
        board[i][j] = '.';
        return 0;
    }
    void solve(vector<vector<char>>& board, int rules[3][9][9]) {
        bool solved = dfs(board, 0, rules);
        if (!solved) cout << "No solution." << endl;
        else
            show(board);
    }
    void getNew(vector<vector<char>>& board, int rules[3][9][9]) {
        memset(rules, 0, sizeof(rules[0][0][0]) * 243);
        for (int i = 0; i < 9; i++)
            fill(board[i].begin(), board[i].end(), '.');
        int cnt = 18, c2 = 1;
        srand (time(NULL));
        while (cnt) {
            int k = rand()%81, c =(c2++)%9, i = k/9, j = k%9;;
            if (board[i][j] == '.' && !rules[0][i][c] &&
                    !rules[1][j][c] && !rules[2][i/3*3+j/3][c]) {
                board[i][j] = '1'+c;
                rules[0][i][c] = rules[1][j][c] = rules[2][i/3*3+j/3][c] = 1;
                cnt--;
            } else {
                c2--;
            }
        }
    }
    void get(vector<vector<char>>& board, int rules[3][9][9]) {
        getNew(board, rules);
        while (!dfs(board, 0, rules)) getNew(board, rules);
        int cnt = 80;
        srand (time(NULL));
        while (cnt--) {
            int k = rand()%81, i = k/9, j = k%9;;
            if (board[i][j] != '.') {
                char c = board[i][j] - '1';
                board[i][j] = '.';
                rules[0][i][c] = rules[1][j][c] = rules[2][i/3*3+j/3][c] = 0;
            }
        }
        show(board);
    }

int main(){
    /*
     *@Author: Shuo Wang PHD
     *@Language: C++
     *@Date modified: 2016-08-12
     * Sudoku game
     */
    int rules[3][9][9];
    vector<vector<char>> board(9, vector<char>(9));
    cout <<"Welcome to Sudoku game."<< endl << endl;
    get(board, rules);
    char c;
    while (cin >> c) {
        if (c == 'g') get(board, rules);
        else if (c == 's') solve(board, rules);
        else if (c == 'e') return 0;
        else
            cout << "Invalid input. Enter g to get new game, s to solve,"
                    " or e to exit." << endl;
    }
    return 0;
}