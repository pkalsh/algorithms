/*
** Baekjoon Algorithm
** bfs #2667 단지번호붙이기
*/

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

typedef struct Point {
    int row;
    int col;
} point;

vector<int> dr = {0, 1, 0, -1};
vector<int> dc = {1, 0, -1, 0};

vector<vector<int> > mat;
vector<vector<bool> > discovered;
vector<int> house_num;
int components = 0; // 단지 개수

void init();
void bfs(point);
void bfsAll();
void printResult();

int main() {
    init();
    bfsAll();
    printResult();
    return 0;
}

void init() {
    int N;
    cin >> N;
    mat.assign(N+2, vector<int>(N+2,-1));
    discovered.assign(N+2, vector<bool>(N+2, true));

    string temp;
    for (int i = 1; i <= N; i++) {
        cin >> temp;
        for (int j = 1; j <= N; j++) {
            mat[i][j] = temp.at(j-1) - '0';
            discovered[i][j] = false;
        }
    }

}

void bfs(point start) {
    int cnt = 1;
    queue<point> q;
    q.push(start);

    // 컴포넌트의 시작점이 아니거나 발견한 좌표면
    if (mat[start.row][start.col] != 1 || discovered[start.row][start.col]) {
            discovered[start.row][start.col] = true; // 발견한 좌표라고 체크하고
            return; // 호출을 끝낸다.
    }
    discovered[start.row][start.col] = true;
    while(!q.empty()) {
        // mat 값이 1인 좌표만 큐에 들어올 수 있다.
        point here = q.front();
        q.pop();
        
        for (int i = 0; i < dr.size(); i++) {
            int trow = here.row + dr[i];
            int tcol = here.col + dc[i];
            // 갈 수 있고 아직 발견되지 않았으면 큐에 넣는다.
            if (mat[trow][tcol] == 1 && !discovered[trow][tcol]) {
                q.push(point{trow, tcol});
                discovered[trow][tcol] = true;
                cnt++;
            }
        }
    }
    house_num.push_back(cnt);
    components++;
}

void bfsAll() {
    for (int r = 0; r < mat.size(); r++) {
        for (int c = 0; c < mat[r].size(); c++) {
            bfs(point{r,c});
        }
    }
}

void printResult() {
    sort(house_num.begin(), house_num.end());
    cout << components << "\n";
    for (int i=0;i<house_num.size(); i++)
        cout << house_num[i] << "\n";
}