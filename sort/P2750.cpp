
// N이 1이상 1000이하
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int N;
vector<int> numbers;

void getInput() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
}
void swap(int src, int dst) {
    int tmp = numbers[src];
    numbers[src] = numbers[dst];
    numbers[dst] = tmp;
}

// selection sort
void sort() {
    for (int i = 0; i < N; i++) {
        int min = i;
        for (int j = i + 1; j < N; j++) {
            if (numbers[j] < numbers[min]) {
                min = j;
            }
        }
        swap(i, min);
    }
}
void print() {
    for (const auto& number:numbers) {
        cout << number << endl;
    }
}

int main() {
    getInput();
    sort();
    print();
}