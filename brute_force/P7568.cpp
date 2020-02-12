#include <iostream>
#include <vector>
using namespace std;

typedef struct {
    int weight;
    int height;
} psize;

int N;
vector<psize> psizes;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int hei, wei;
        cin >> wei >> hei;
        psizes.push_back(psize{wei, hei});
    }
}

bool isBigger(psize p1, psize p2) {
    return p1.height > p2.height && p1.weight > p2.weight;
}
void solution() {
    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (isBigger(psizes[j], psizes[i])) {
                count++;
            }
        }
        cout << count + 1 << " ";
    }
}

int main() {
    init();
    solution();
}