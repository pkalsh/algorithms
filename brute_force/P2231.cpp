#include <iostream>
#include <string>

using namespace std;
int N;

void init() {
    cin >> N;
}
int getDecomposition(int n) {
    string stringN = to_string(n);
    int sum = n;
    for (int i = 0; i < stringN.length(); i++) {
        sum += stringN.at(i) - '0';
    }
    return sum;
}
void solution() {   
    for (int i = 1; i <= N; i++) {
        if (getDecomposition(i) == N) {
            cout << i;
            return;
        }
    }
    cout << 0;
}

int main() {
    init();
    solution();
    return 0;
}