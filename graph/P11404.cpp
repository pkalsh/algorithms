#include <iostream>
#include <vector>

using namespace std;
const int MAX_COST = 100001;

int vertexNum;
int edgeNum;
vector<vector<int> > adj;

void init() {
    cin >> vertexNum >> edgeNum;
    adj.assign(vertexNum, vector<int>(vertexNum, MAX_COST));
    for (int i = 0; i < edgeNum; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        if (adj[from-1][to-1] != MAX_COST) {
            adj[from-1][to-1] = min(adj[from-1][to-1], cost);
            continue;
        }
        adj[from-1][to-1] = cost;
    }
}

void floyd() {
    for (int i = 0; i < vertexNum; i++) {
        adj[i][i] = 0;
    }

    for (int k = 0; k < vertexNum; k++) {
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                if (adj[i][j] > adj[i][k] + adj[k][j]) {
                    adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
    }
}

void turnInfToZero() {
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (adj[i][j] == MAX_COST) {
                adj[i][j] = 0;
            }
        }
    }
}

void printAdj() {
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    init();
    floyd();
    turnInfToZero();
    printAdj();
    return 0;
}