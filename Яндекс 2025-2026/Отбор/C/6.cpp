#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int a, b;
        cin >> a >> b;
        int c = b - a;
        if (c >= 0 && (c | a) == c) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
