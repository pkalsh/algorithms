#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

const int ROW = 12, COL = 6;
int count = 0;

typedef struct Pos {
    int row;
    int col;
} Pos;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

vector<string> board;
vector<vector<bool> > discovered;
vector<Pos> cached;
pair<Pos, Pos> blockOnPoint;

void init() {
    cached.clear();
    discovered.assign(ROW, vector<bool>(COL, false));
}

void getInput() {
    for (int i = 0; i < ROW; i++) {
        string tmp;
        cin >> tmp;
        board.push_back(tmp);
    }

    init();
}

bool isInRange(Pos pos) {
    return pos.row >= 0 && pos.row < ROW && pos.col >= 0 && pos.col < COL;
}

int bfs(Pos pos) {
    int chunkSize = 1;
    int row = pos.row, col = pos.col;
    queue<Pos> q;

    q.push(pos);
    discovered[row][col] = true;

    if (board[row][col] == '.') return 0;

    while (!q.empty()) {
        Pos here = q.front();
        cached.push_back(here);
        char blockColor = board[here.row][here.col];
        q.pop();

        for (int i = 0; i < 4; i++) {
            Pos there = Pos{here.row + dr[i], here.col + dc[i]};
            // isInRange 검사를 따로 빼서 할지?
            if (isInRange(there) && board[there.row][there.col] == blockColor && !discovered[there.row][there.col]) {
                q.push(there);
                cached.push_back(there);
                discovered[there.row][there.col] = true;
                chunkSize++;
            }
        }
    }

    if (chunkSize < 4) {
        init();
    }
    return chunkSize;
}

bool isAbleToBeRemoved() {
    vector<Pos> cachedBuffer;
    vector<Pos> temp;
    int flag = false;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            int chunkSize = bfs(Pos{i, j});
            if (chunkSize >= 4) {
                temp.assign(cached.begin(), cached.end());
                for (int i = 0; i < temp.size(); i++) {
                    cachedBuffer.push_back(temp[i]);
                }
                flag = true;
            }
        }
    }
    
    if (flag) {
        cached.clear();
        cached.assign(cachedBuffer.begin(), cachedBuffer.end());
        return true;
    }
    return false;
}

void removeAdjacentBlocks() {
    for (int i = 0; i < cached.size(); i++) {
        int row = cached[i].row; int col = cached[i].col;
        board[row][col] = '.';
    }   
}

bool isBlockOnPoint() {
    for (int i = 1; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (board[i][j] == '.' && board[i-1][j] != '.') {
                blockOnPoint.first = Pos{i-1, j};
                blockOnPoint.second = Pos{i, j};
                return true;
            }
        }
    }
    return false;
}

void replaceAdjacentOnes() {
    Pos block = blockOnPoint.first;
    Pos point = blockOnPoint.second;

    board[point.row][point.col] = board[block.row][block.col];
    board[block.row][block.col] = '.';
}

void printResult() {
    cout << count;
}

void printBoard() {
    for (int i = 0; i < ROW; i++) {
        cout << board.at(i) << endl;
    }
}

int main() {
    getInput();
    while (isAbleToBeRemoved()) {
        count++;
        removeAdjacentBlocks();
        while (isBlockOnPoint()) {
            replaceAdjacentOnes();
        }
        // printBoard();
        init();
    }
    printResult();

    // printBoard();
}