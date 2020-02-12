#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

int M, N;
vector<string> board;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        board.push_back(row);
    }
}

int whiteCheck(vector<string> eightboard) {
    int count = 0;
    for (int i = 0; i < 8; i++ ) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 0 && j % 2 == 0 ) {
                if (eightboard[i][j] == 'B')
                    count++;
            }
            else if (i % 2 == 0 && j % 2 == 1) {
                if (eightboard[i][j] == 'W')
                    count++;
            }
            else if (i % 2 == 1 && j % 2 == 0) {
                if (eightboard[i][j] == 'W')
                    count++;
            }
            else {
                if (eightboard[i][j] == 'B') 
                    count++;
            }
        }
    }
    return count;
}
int blackCheck(vector<string> eightboard) {
    int count = 0;
    for (int i = 0; i < 8; i++ ) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 0 && j % 2 == 0 ) {
                if (eightboard[i][j] == 'W')
                    count++;
            }
            else if (i % 2 == 0 && j % 2 == 1) {
                if (eightboard[i][j] == 'B')
                    count++;
            }
            else if (i % 2 == 1 && j % 2 == 0) {
                if (eightboard[i][j] == 'B')
                    count++;
            }
            else {
                if (eightboard[i][j] == 'W') 
                    count++;
            }
        }
    }
    return count;
}
vector<string> splitEight(int row, int col) {
    vector<string> ret;
    for (int i = 0; i < 8; i++) {
        string tmp = board[row + i].substr(col, 8);
        ret.push_back(tmp);
    }

    return ret;
}
void solution() {
    int min = numeric_limits<int>::max();
    for (int row = 0; row < N-7; row++) {
        for (int col = 0; col < M-7; col++) {
            vector<string> split = splitEight(row, col);
            int white = whiteCheck(split);
            int black = blackCheck(split);
            int less = (white>black? black:white);
            if (min > less) min = less;
        }
    }
    cout << min;
}

int main() {
    init();
    solution();
    return 0;
}