#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
bool isSatisfied(string row, vector<string> condition) {
    bool ret = true;
    for (int i =0; i < condition.size(); i++) {
        if (!ret) return false;
        char first = condition[i][0];
        char second = condition[i][2];
        int fidx = row.find(first);
        int sidx = row.find(second);

        int difference = abs(fidx - sidx) - 1;
        int goal = condition[i][4] - '0';
        switch (condition[i][3]) {
        case '=':
            ret &=  (difference == goal);
            break;
        case '>':
            ret &=  (difference > goal);
            break;
        case '<':
            ret &=  (difference < goal);
            break;
        }
    }

    return ret;
}

int solution(int n, vector<string> data) {
	int answer = 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;

	string friends = "ACFJMNRT";
	do {
		if (!isSatisfied(friends, data)) {
			answer -= 1;
		}
	} while (next_permutation(friends.begin(), friends.end()));


	return answer;
}

int main() {
	cout << solution(2, { "N~F=0", "R~T>2" });
	return 0;
}