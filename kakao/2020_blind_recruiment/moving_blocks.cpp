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
    int isVertical;
}
robotPos;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
bool isrev[4] = {true, true, false, false};
bool isfir[4] = {true, false, true, false};

// first 기준
// [0] 가로 방향 visit 체크
// [1] 세로 방향 visit 체크 
vector<vector<int> >discovered[2];

void init(vector<vector<int> >&);
void makeNewGraph(vector<vector<int> >&);
bool canRotate(vector<vector<int> >&, robotPos&, bool, bool);
void rotateRobot(robotPos&, bool, bool);
bool canMove(vector<vector<int> >&, robotPos&, point);
bool isDiscovered(robotPos&, point);
int solution(vector<vector<int> >);

void init(vector<vector<int> >& board) {
	makeNewGraph(board);
	discovered[0] = board;
    discovered[1] = board;
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
bool canRotate(vector<vector<int> >& board, robotPos& now, bool rotReverse, bool rotFirst) {
    int bottom_first = board[now.first.row + 1][now.first.col];
    int bottom_second = board[now.second.row + 1][now.first.col];
    int up_first = board[now.first.row - 1][now.first.col];
    int up_second = board[now.second.row - 1][now.second.col];

    if (rotReverse) {
        if (rotFirst) {
            if (!up_first && !up_second ) {
                return true;
            }
            return false;
        }
        else {
            if (!bottom_first && !bottom_second) {
                return true;
            }
            return false;
        }
    }
    else {
        if (rotFirst) {
            if (!bottom_first && !bottom_second) {
                return true;
            }
            return false;
        }
        else {
            if (!up_first && !up_second) {
                return true;
            }
            return false;
        }
    }
}
void rotateRobot(robotPos & now, bool rotReverse, bool rotFirst) {
    // 회전할 수 있는지 없는지 판단은 다른 메소드 몫
	// rotReverse -> 시계 반대방향, rotFirst -> first를 축으로
    point old_first = now.first;
    point old_second = now.second;

    if (!now.isVertical) {
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
        // 세로 방향이 된 first 위치를 visit 처리
        discovered[now.first.row][now.first.col][1] = 1;
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
        // 가로 방향이 된 first 위치를 visit 처리
        discovered[now.first.row][now.first.col][0] = 1;
    }
}
bool canMove(vector<vector<int> >& board, robotPos& now, point direction) {
    int destF, destS;
    destF = board[now.first.row + direction.row][now.first.col + direction.col];
    destS = board[now.second.row + direction.row][now.second.col + direction.col];

    if (now.isVertical) {
        if (direction.row == 0) {
            return (!destF && !destS);
        }
        else {
            if (direction.row < 0) {
                return !destF;
            }
            else {
                return !destS;
            }
        }
    }
    else {
        if (direction.row == 0) {
            if (direction.col < 0) {
                return !destF;
            }
            else {
                return !destS;
            }
        }
        else {
            return (!destF && !destS);
        }
    }
}
bool isDiscovered(robotPos& now, point direction) {
    if (!now.isVertical) {
        // 가로 방향일때
        return discovered[now.first.row + direction.row][now.first.col + direction.col][0];
    }
    else {
        return discovered[now.first.row + direction.row][now.first.col + direction.col][1]; 
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
	
	init(board);
    int dest_pos = board.size() - 2;
	// BFS
	queue<robotPos> q;
	q.push(robotPos{point{1,1}, point{1,2}, false});
	discovered[1][1][0] = 1;
    int be_processed = q.size();

	while (!q.empty()) {
		robotPos now_pos = q.front();
        // 도달하면 반복문 탈출
        if (now_pos.second.row == dest_pos && now_pos.second.col == dest_pos) 
            break;
        if (be_processed == 0) {
            be_processed = q.size();
            answer++;
        }

		q.pop();
        be_processed--;
		
        // 이동
        for (int i = 0; i < sizeof(dr)/sizeof(int); i++) {
            point dir = {dr[i], dc[i]};
            if (canMove(board, now_pos, dir) && !isDiscovered(now_pos, dir)) {
                robotPos new_pos;
                new_pos.first = {now_pos.first.row + dir.row, now_pos.first.col + dir.col};
                new_pos.second = {now_pos.second.row + dir.row, now_pos.second.col + dir.col};
                new_pos.isVertical = now_pos.isVertical;

                q.push(new_pos);
                discovered[now_pos.first.row + dir.row][now_pos.first.col + dir.col][now_pos.isVertical] = 1;
            }
        }
        // 회전
        for (int j = 0; j < sizeof(isrev)/sizeof(bool); j++) {
            bool rot_reverse = isrev[j];
            bool rot_first = isfir[j];
            if (canRotate(board, now_pos, rot_reverse, rot_first)) {
                robotPos new_pos = now_pos;
                rotateRobot(new_pos, rot_reverse, rot_first);
                q.push(new_pos);
            }
        }
	}
	
    return answer;
}