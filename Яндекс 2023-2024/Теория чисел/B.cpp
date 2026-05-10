#include<bits/stdc++.h>

using namespace std;

signed main() {
    int a, b, c;
    cin >> a >> b >> c;
    int cl = c % b;
    for (int i = 0; i < b; ++i) {
        if (i * a % b == cl) {
            cout << i << " " << (c - i * a) / b << endl;
            return 0;
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
