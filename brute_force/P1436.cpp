#include <iostream>
using namespace std;

int N;

void init() {
    cin >> N;
}
bool check(string num) {
    int count = 3;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '6') {
            count--;
        } else {
            count = 3;
        }

        if (!count) return true;
    }
    return false;
}

void solution() {
    int num = 0;
    while(N > 0) {
        num++;
        string snum = to_string(num);
        if (check(snum)) {
            N--;
        }
    }
    cout << num;
}

int main() {
    init();
    solution();
    return 0;
}