#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

typedef struct {
    bool isWater; // 0: beaver & hedge, 1: water
    int row;
    int col;
    int time;
} point;

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

vector<string> forest;
point hedge_pos;
point beaver_pos;
vector<point> water_pos;
vector<vector<bool> > water_visited;
vector<vector<bool> > hedge_visited;
int R,C;
int result;

void init() {
    cin >> R >> C;
    water_visited.assign(R, vector<bool>(C, true));
    hedge_visited.assign(R, vector<bool>(C, true));

    for (int i = 0; i < R; i++) {
        string str;
        cin >> str;
        forest.push_back(str);
        for (int j = 0; j < C; j++) {
            switch(str[j]) {
            case 'S':
                hedge_pos = {false, i, j, 0};
                break;
            case '*':
                water_pos.push_back({true, i, j, 0});
                break;
            case 'D':
                beaver_pos = {false, i, j, 0};
                break;
            }
            water_visited[i][j] = false;
            hedge_visited[i][j] = false;
        }
    }
}

bool isInRange(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

bool isValid(point pos) {
    int nr = pos.row;
    int nc = pos.col;

    if (pos.isWater) {
        return isInRange(nr, nc) && !water_visited[nr][nc] && forest[nr][nc] != 'X' && forest[nr][nc] != 'D';
    } else {
        return isInRange(nr, nc) && !hedge_visited[nr][nc] && forest[nr][nc] != 'X' && !water_visited[nr][nc]; 
    }
}

void hedgeGoWaterFlow() {
    queue<point> q;
    for (int i = 0; i < water_pos.size(); i++) {
        q.push(water_pos[i]);
        water_visited[water_pos[i].row][water_pos[i].col] = true;
    }
    q.push(hedge_pos);
    hedge_visited[hedge_pos.row][hedge_pos.col] = true;

    while (!q.empty()) {
        point now = q.front();
         if (now.row == beaver_pos.row && now.col == beaver_pos.col) {
            result = now.time;
            break;
        }
        q.pop();
        for (int j = 0; j < 4; j++) {
            point later = {now.isWater, now.row + dr[j], now.col + dc[j], now.time + 1};
            if (isValid(later)) {
                q.push(later);
                (later.isWater ? water_visited[later.row][later.col] : hedge_visited[later.row][later.col]) = true;
            }
        }
    }
}

void printResult() {
    if (hedge_visited[beaver_pos.row][beaver_pos.col]) {
        cout << result;
        return;
    }
    cout << "KAKTUS";
}

int main() {
    init();
    hedgeGoWaterFlow();
    printResult();
    return 0;
}