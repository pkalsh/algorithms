#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C;
vector<vector<int> > iceberg;
vector<vector<bool> > visited;

typedef struct Point {
    int row;
    int col;
} point;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

int years = 0;

void init() {
    cin >> R >> C;
    iceberg.assign(R+2, vector<int>(C+2, -1));
    visited.assign(R+2, vector<bool>(C+2, true));

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> iceberg[i][j];
            visited[i][j] = false;
        }
    }
}

void reset() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            visited[i][j] = false;
        }
    }
}

void bfs(point start) {
    queue<point> q;
    q.push(start);
    visited[start.row][start.col] = true;
    while (!q.empty()) {
        point here = q.front();
        q.pop();
        for (int i = 0; i < sizeof(dr)/sizeof(int); i++) {
            int nextR = here.row + dr[i];
            int nextC = here.col + dc[i];
            if (iceberg[nextR][nextC] != 0 && iceberg[nextR][nextC] != -1 && !visited[nextR][nextC]) {
                q.push(point{nextR, nextC});
                visited[nextR][nextC] = true;
            }
        }
    }
}

int getNumOfChunks() {
    int ret = 0;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (iceberg[i][j] != 0 && !visited[i][j]) {
                bfs(point{i, j});
                ret++;
            }
        }
    }
    return ret;
}

int getNearZero(vector<vector<int> >& ice, point now) {
    int ret = 0;
    for (int i = 0; i < sizeof(dr)/sizeof(int); i++) {
        int nearR = now.row + dr[i];
        int nearC = now.col + dc[i];
        if (!ice[nearR][nearC])
            ret++;
    }
    return ret;
}

void meltIceberg() {
    vector<vector<int> > temp;
    temp = iceberg;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (temp[i][j] != 0) {
                iceberg[i][j] -= getNearZero(temp, point{i,j});
                if (iceberg[i][j] < 0) iceberg[i][j] = 0;
            }
        }
    }
    years++;
}

int main() {
    init();
    int num_chunks;
    while((num_chunks = getNumOfChunks()) < 2) {
        if (num_chunks == 0) {
            cout << "0";
            return 0;
        }
        meltIceberg();
        reset();
    }

    cout << years;
    return 0;
}