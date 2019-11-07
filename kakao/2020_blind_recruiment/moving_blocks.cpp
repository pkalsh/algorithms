#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct Point {
    int row;
    int col;
}
point;

typedef struct RobotPos {
    point first;
    point second;
}
robotPos;

bool isHorizontal = true;

vector<vector<int> >discovered;

void init(vector<vector<int> >& board) {
	makeNewGraph(board);
	discovered = board;	
}
void makeNewGraph(vector < vector<int> >& board) {
    size_t old_size = board.size();
    vector < vector<int> > temp;
    temp.assign(old_size + 2, vector<int>(old_size + 2, 1));
    for (int i = 1; i <= old_size; i++) {
        for (int j = 1; j <= old_size; j++) {
            temp[i][j] = board[i - 1][j - 1];
        }
    }
    board = temp;
}
void rotateRobot(robotPos & now, bool rotReverse, bool rotFirst) {
    // 회전할 수 있는지 없는지 판단은 다른 메소드 몫
	// rotReverse -> 시계 반대방향, rotFirst -> first를 축으로
    point old_first = now.first;
    point old_second = now.second;

    if (isHorizontal) {
        // 가로 방향일때
        if (rotReverse) {
            // 시계 반대 방향으로 돌린다.
            if (rotFirst) {
                // first를 축으로 돌린다.
                now.first = point {
                    old_second.row - 1,
                    old_second.col - 1
                };
                now.second = old_first;
            } else {
                // second를 축으로 돌린다.
                now.first = old_second;
                now.second = point {
                    old_second.row + 1,
                    old_second.col
                };
            }
        } else {
            // 시계 방향으로 돌린다.
            if (rotFirst) {
                // first를 축으로 돌린다.
                now.second = point {
                    old_second.row + 1,
                    old_second.col
                };
            } else {
                // second를 축으로 돌린다.
                now.first = point {
                    now.first.row - 1,
                    now.first.col + 1
                };
            }
        }
    } else {
        // 세로 방향일때
        if (rotReverse) {
            // 시계 반대 방향으로 돌린다.
            if (rotFirst) {
                // first를 축으로 돌린다.
                now.second = point {
                    old_second.row - 1,
                    old_second.col + 1
                };
            } else {
                // second를 축으로 돌린다.
                now.first = point {
                    old_first.row + 1,
                    old_first.col - 1
                };
            }
        } else {
            // 시계 방향으로 돌린다.
            if (rotFirst) {
                // first를 축으로 돌린다.
                now.first = point {
                    old_second.row - 1,
                    old_second.col - 1
                };
                now.second = old_first;
            } else {
                // second를 축으로 돌린다.
                now.first = old_second;
                now.second = point {
                    old_first.row + 1,
                    old_first.col + 1
                };
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
	
	init(board);
	// BFS
	queue<robotPos> q;
	q.push(robotPos{point{1,1},point{1,2}});
	discovered[1][1] = 1;

	while (!q.empty()) {
		robotPos now_pos = q.front();
		q.pop();
		
	}
	
    return answer;
}

// isHorizontal이 true이고 점이 <N, N-1>에 도달하거나 false이고 점이 <N-1, N>에 도달하면 성공이다.