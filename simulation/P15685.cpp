#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int x;
    int y;
    int dir;
    int gen;
} startInform;

typedef struct {
    int x;
    int y;
} point;

vector<startInform> curves;
vector<vector<bool> > map;
int N;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
int cnt = 0;

void init() {
    cin >> N;
    int x, y, d, g;
    for (int i = 0; i < N; i++) {
        cin >> x >> y >> d >> g;
        curves.push_back(startInform{x, y, d, g});
    }

    map.assign(101, vector<bool> (101, false));
}

bool isInRange(point v) {
    return v.x >=0 && v.x <= 100 && v.y >= 0 && v.y <= 100;
} 

void checkVertex(point v) {
    map[v.y][v.x] = true;
}

void rotateCurve(vector<point>& vertices) {
    point axis = vertices.back();
    int size = vertices.size() - 1;
    for (int i = size; i >= 0; i--) {
        int difx = vertices[i].x - axis.x;
        int dify = vertices[i].y - axis.y;
        point new_vertex = {axis.x - dify, axis.y + difx};
        if (isInRange(new_vertex)) {
            vertices.push_back(new_vertex);
            checkVertex(new_vertex);
        }
    }

}

void drawMoreThanOne(vector<point> vertices, int gen, int now_gen) {
    if (now_gen > gen) return;
    rotateCurve(vertices);
    drawMoreThanOne(vertices, gen, now_gen + 1);
}

void drawDragonCurves() {
    for (int i = 0; i < curves.size(); i++) {
        vector<point> vertices;
        int generation = curves[i].gen;
        point vertex = point{curves[i].x, curves[i].y};
        vertices.push_back(vertex);
        checkVertex(vertex);
        int direction = curves[i].dir;
        point nextVertex = point{vertex.x + dx[direction], vertex.y + dy[direction]};
        if (isInRange(nextVertex)) {
            vertices.push_back(nextVertex);
            checkVertex(nextVertex);
            drawMoreThanOne(vertices, generation, 1);    
        }            
            
    }
}


bool isCheckedSquare(int x, int y) {
    return map[y+1][x] && map[y][x+1] && map[y+1][x+1];
}

void countSquare() {
    for (int i = 0; i < map.size() - 1; i++) {
        for (int j = 0; j < map[i].size() - 1; j++) {
            if (map[j][i] && isCheckedSquare(i, j)) {
                cnt++;
            }
        }
    }
}

void printResult() {
    cout << cnt;
}

int main() {
    init();
    drawDragonCurves();
    countSquare();
    printResult();
    return 0;
}