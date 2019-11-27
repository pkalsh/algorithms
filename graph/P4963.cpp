#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int w, h;
int landNum;
vector<vector<int> > map;
vector<vector<bool> > visited;

typedef struct Pos {
    int row;
    int col;
} Pos;

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void init() {
    landNum = 0;
    map.assign(h, vector<int>(w, -1));
    visited.assign(h, vector<bool>(w, false));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> map[i][j];
        }
    }
}

void checkVisited(Pos pos) {
    visited[pos.row][pos.col] = true;
}

bool isInRange(Pos pos) {
    return (pos.row >= 0 && pos.row < h && pos.col >= 0 && pos.col < w);
}

bool isVisited(Pos pos) {
    return visited[pos.row][pos.col];
}

bool isAbleToGo(Pos pos) {
    return map[pos.row][pos.col];
}

void bfs(Pos start) {
    queue<Pos> q;
    q.push(start);
    checkVisited(start);

    while(!q.empty()) {
        Pos here = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            Pos there = {here.row + dr[i], here.col + dc[i]};
            if (isInRange(there) && !isVisited(there) && isAbleToGo(there)) {
                q.push(there);
                checkVisited(there);
            }
        }
    }
     
}

void bfsAll() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (!isVisited({i, j}) && isAbleToGo({i, j})) {
                bfs({i, j});
                landNum++;
            }
        }
    }
}

int main() {
    do {
        cin >> w >> h;
        if (w && h) {
            init();
            bfsAll();
            cout << landNum << "\n";
        }
    } while(w || h);  

    return 0;  
}