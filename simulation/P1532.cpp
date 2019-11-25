#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAX_COINS = 1000000;

typedef struct {
    int gold, silver, bronze;
    int step;
} Coins;

Coins (*HowTo[4])(Coins&);
Coins now, goal;
map<Coins, bool> visited;

bool success = false;
int result;

Coins goldToSilver(Coins& now) {
    return Coins{now.gold - 1, now.silver + 9, now.bronze, now.step + 1};
}
Coins silverToGold(Coins& now) {
    return Coins{now.gold + 1, now.silver - 11, now.bronze, now.step + 1};
}
Coins silverToBronze(Coins& now) {
    return Coins{now.gold, now.silver - 1, now.bronze + 9, now.step + 1};
}
Coins bronzeToSilver(Coins& now) {
    return Coins{now.gold, now.silver + 1, now.bronze - 11, now.step + 1};
}

void init() {
    cin >> now.gold >> now.silver >> now.bronze >> goal.gold >> goal.silver >> goal.bronze;
    now.step = 0;

    HowTo[0] = goldToSilver;
    HowTo[1] = silverToGold;
    HowTo[2] = silverToBronze;
    HowTo[3] = bronzeToSilver;
}

void visitCheck(Coins coin) {
    visited[coin] = true;
}

bool isVisited(Coins coin) {
    
}

bool isAbleToTrade(Coins coin) {
    return coin.gold >= 0 && coin.silver >= 0 && coin.bronze >= 0 && 
           coin.gold <= MAX_COINS && coin.silver <= MAX_COINS && coin.bronze <= MAX_COINS;
}

bool isReachedToGoal(Coins coin) {
    return coin.gold >= goal.gold && coin.silver >= goal.silver && coin.bronze >= goal.bronze;
}

void tradeCoins() {
    queue<Coins> q;
    q.push(now);
    visitCheck(now);

    while (!q.empty()) {
        Coins prev = q.front();
        if (isReachedToGoal(prev)) {
            success = true;
            result = prev.step;
            return;
        }

        q.pop();
        for (int i = 0; i < 4; i++ ) {
            Coins traded = HowTo[i](prev);
            if (!isAbleToTrade(traded)) {
                continue;
            }
            if (!isVisited(traded)) {
                q.push(traded);
                visitCheck(traded);
            }
        }
    }
}

void printResult() {
    if (success)
        cout << result;
    else 
        cout << "-1";

}

int main() {
    init();
    tradeCoins();
    printResult();
    return 1;
}