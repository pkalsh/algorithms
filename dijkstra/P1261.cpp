// 우선순위큐 다익스트라
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef struct Pos {
    int row;
    int col;
} Pos;
typedef pair<int, Pos> pi;
bool operator<(pi t, pi u) {
    return t.first < u.first;
} 

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

vector<string> map;
vector<vector<int> > dist;

int M,N;

void getInput() {
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        map.push_back(tmp);
    }

    dist.assign(N, vector<int>(M, 1000));
    dist[0][0] = 0;
}

bool isInRange(int r, int c) {
    return r>=0 && r<N && c>=0 && c<M;
}

void minimumCrash() {
    dist[0][0] = 0; 
 
    priority_queue<pi, vector<pi>, less<pi> > pq;
    pq.push(make_pair(0, Pos{0,0}));
 
    while (!pq.empty())
    {
        int cost = -pq.top().first;
        Pos here = pq.top().second; 
 
        pq.pop();
 
        if (dist[here.row][here.col] < cost)
            continue;
        
        for (int i = 0; i < 4; i++) {
            int r = here.row + dr[i];
            int c = here.col + dc[i];
            if (isInRange(r,c)) {
                Pos there = Pos{r, c};
                int integerMapCost = map[there.row][there.col] - '0';
                int nextDist = cost + integerMapCost;

                if (dist[there.row][there.col] > nextDist)
                {
                    // cout << r << "," << c << ":" << nextDist << endl;
                    dist[there.row][there.col] = nextDist;
                    pq.push(make_pair(-nextDist, there));
                }
            }
            
        }
    }
}

void printDist() {
    for (int i = 0; i < N; i++ ) {
        for (int j = 0; j < M ; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    getInput();
    minimumCrash();
    cout << dist[N-1][M-1];
    // printDist();
}