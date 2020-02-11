#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int M, N;
vector<int> cards;

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int cardNum;
        cin >> cardNum;
        cards.push_back(cardNum);
    }
}

int getDifference(int sum) {
    return M - sum;
}

void solution() {
    int dif = numeric_limits<int>::max();
    int ret;
    
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N && j != i; j++) {
            for (int k = 2; k < N && k != i && k != j; k++) {
                int sum = cards[i] + cards[j] + cards[k];
                int tmp = getDifference(sum);
                if (tmp >= 0 && dif > tmp) {
                    dif = tmp;
                    ret = sum;
                }
            }
        }
    }

    cout << ret;
}

int main() {
    init();
    solution();
}