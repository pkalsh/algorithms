/*
** Baekjoon Algorithm
** bfs #1697 숨바꼭질
*/
#include <iostream>
#include <queue>

using namespace std;

const int MAX_LENGTH = 100000;
int N, K;
int map[MAX_LENGTH + 1];
int (*moveTo[3])(int&); // 움직이는 방법을 담는 함수 포인터 배열


void init();
void find();
bool isOutOfRange(int);
void printResult();

int backWalk(int& now) {
	return now - 1;
}
int frontWalk(int& now) {
	return now + 1;
}
int teleport(int& now) {
	return now * 2;
}

int main() {
	init();
	find();
	printResult();
}

void init() {
	cin >> N >> K;
	fill_n(map, MAX_LENGTH + 1, -2); // map을 -2로 초기화
	map[N] = 0;
	map[K] = -1;
	moveTo[0] = backWalk;
	moveTo[1] = frontWalk;
	moveTo[2] = teleport;
}

void find() {
	queue<int> q;
	q.push(N);

	int time = 1; // 현재 시간
	unsigned int be_processed = q.size();

	while (map[K] == -1) {
		int now = q.front();
		q.pop();
		be_processed--;

		for (int i = 0; i < sizeof(moveTo) / sizeof(moveTo[0]); i++) {
			int next = moveTo[i](now);
			if (isOutOfRange(next)) continue;
			if (map[next] == -2) {
				// 아직 발견하지 않았다면 큐에 넣고 시간 체크
				q.push(next);
				map[next] = time;
			}
		}
		if (be_processed == 0) {
			time++;
			be_processed = q.size();
		}
	}
}

bool isOutOfRange(int idx) {
	return (idx < 0 || idx > MAX_LENGTH);
}

void printResult() {
	cout << map[K];
}