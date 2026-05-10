#include<iostream>
#include<vector>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    int x = min(m, n / 2);
    for (int i = 0; i < x; ++i) {
        cout << "GGB";
    }
    m -= x;
    n -= x * 2;
    for (int i = 0; i < n; ++i) {
        cout << "G";
    }
    for (int i = 0; i < m; ++i) {
        cout << "B";
    }
    return 0;
}
