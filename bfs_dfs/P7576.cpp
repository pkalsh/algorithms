/*
** Baekjoon Algorithm
** bfs #7576 토마토
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef struct Point {
	int row;
	int col;
} point;

vector<vector<int> > box;
vector<point> start_pos;

vector<int> dr = { 0, 1, 0, -1 };
vector<int> dc = { 1, 0, -1, 0 };

int days = 0;
int M, N;
int zero_num = 0;

void init();
void ripenTomatoes();
bool isAllTomatoesRipened();
bool isOutOfRange(int, int);
void printResult();

int main() {
	init();
	ripenTomatoes();
	printResult();
	return 0;
}

void init() {
	cin >> M >> N;
	box.assign(N, vector<int>(M, -1));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> box[r][c];
			// 익은 토마토의 위치를 캐싱
			if (box[r][c] == 1)
				start_pos.push_back(point{ r,c });
            if (box[r][c] == 0)
                zero_num++;
		}
	}
}

void ripenTomatoes() {
	queue<point> q;
	for (int i = 0; i < start_pos.size(); i++) {
		q.push(start_pos[i]);
	}
	unsigned int be_processed = q.size(); // 오늘 처리할 토마토 개수

	while (!q.empty()) {
		if (isAllTomatoesRipened()) {
			// 모든 토마토가 익었으면 끝낸다.
            // 다 익자마자 함수호출을 끝내므로 days 처리가 안된거 처리
            if (days > 0) days++;
            return;
		}
		if (be_processed == 0) {
			// 오늘 처리할 토마토들을 다 처리하면 다시 현재 처리할 사이즈 갱신
			be_processed = q.size();
			days++;
		}
		point now = q.front();
		q.pop();
		be_processed--;
		for (int i = 0; i < dr.size(); i++) {
			int trow = now.row + dr[i];
			int tcol = now.col + dc[i];
			if (isOutOfRange(trow, tcol)) continue;
			if (box[trow][tcol] == 0) {
				box[trow][tcol] = 1;
                zero_num--;
				q.push(point{ trow,tcol });
			}
		}
	}
}

bool isOutOfRange(int r, int c) {
	return (r < 0 || c < 0 || r >= box.size() || c >= box[0].size());
}

bool isAllTomatoesRipened() {
	if (zero_num == 0)
	    return true;
    return false;
}

void printResult() {
	if (isAllTomatoesRipened()) {
		cout << days;
	}
	else {
		cout << "-1";
	}
}