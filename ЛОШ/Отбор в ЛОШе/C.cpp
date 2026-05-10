#include<iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    ++n; ++m;
    int x = 1, pow = 0;
    while (x < n) {
        x *= 2;
        pow++;
    }
    int x2 = 1, pow2 = 0;
    while (x2 < m) {
        x2 *= 2;
        pow2++;
    }
    cout << pow + pow2 << endl;
    return 0;
}
