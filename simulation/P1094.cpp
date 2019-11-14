#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sticks_len;
int goal_len;

void init() {
    cin >> goal_len;
    sticks_len.push_back(64);
}

int getSum(vector<int> arr) {
    int ret = 0;
    for (int i = 0; i < arr.size(); i++) {
        ret += arr[i];
    }
    return ret;
}

void cutToHalf() {
    int shortest = sticks_len.back();
    int half = shortest / 2;
    sticks_len.pop_back();
    sticks_len.push_back(half);
    sticks_len.push_back(half);
}

void discardSurplus() {
    sticks_len.pop_back();
}

void simulation() {
    while (getSum(sticks_len) > goal_len) {
        sort(sticks_len.begin(), sticks_len.end(), greater<int>());
        cutToHalf();
        vector<int> temp = sticks_len;
        temp.pop_back();
        if (getSum(temp) >= goal_len) {
            discardSurplus();
        }
    }
}

void printResult() {
    cout << sticks_len.size();
}

int main() {
    init();
    simulation();
    printResult();
    return 0;
}