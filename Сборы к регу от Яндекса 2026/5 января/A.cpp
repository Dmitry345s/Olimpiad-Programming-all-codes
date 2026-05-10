#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << -1 << endl;
        return 0;
    }
    if (n % 2 == 0) {
        for (int i = 0; i < n / 2; ++i) {
            cout << 1;
        }
        for (int i = 0; i < n / 2; ++i) {
            cout << 5;
        }
        cout << endl;
        return 0;
    }
    cout << 111;
    for (int i = 0; i < (n - 3) / 2; ++i) {
        cout << 1;
    }
    for (int i = 0; i < (n - 3) / 2; ++i) {
        cout << 5;
    }
    cout << endl;
    return 0;
}
