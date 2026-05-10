#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, w;
    cin >> n >> w;
    bitset<6250001> b;
    b[0] = 1;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        b = (b << a) | b;
    }
    if (b[w]) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
