/*
** Baekjoon Algorithm
** geometric #1002 터렛
*/

#include <iostream>
#include <cmath>
using namespace std;

typedef struct Point{
    int x;
    int y;
} Point;

int T;

int concentric(int r1, int r2);
int notConcentric(float distance, int r1, int r2);
float getDistance(Point a, Point b);

int main() {
    cin >> T;
    for (int t=0; t<T; t++) {
        int answer;
        Point jo, baek;
        int r1, r2;
        cin >> jo.x >> jo.y >> r1 >> baek.x >> baek.y >> r2;
        if (jo.x == baek.x && jo.y == baek.y) {
            answer = concentric(r1, r2);
        } else {
            answer = notConcentric(getDistance(jo, baek), r1, r2);
        }
        cout << answer << '\n';
    }
    return 0;
}

int concentric(int r1, int r2) {
    if (r1 == r2) {
        return -1;
    }
    return 0;
}

int notConcentric(float distance, int r1, int r2) {
    int rsum = r1 + r2;
    if (distance < (double)rsum) return 2;
    else if (distance == (double)rsum) return 1;
    else return 0;
}

float getDistance(Point a, Point b) {
    return sqrt(pow((double)(b.x - a.x), 2.0) + pow((double)(b.y - a.y), 2.0));
}
