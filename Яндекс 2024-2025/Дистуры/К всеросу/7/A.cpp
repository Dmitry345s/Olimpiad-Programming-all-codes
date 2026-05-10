#include<bits/stdc++.h>

#define int long long

using namespace std;

void solve(int l, int r) {
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
    for (int i = l; i < m; ++i) {
        cout << i + 1 << " " << i - l + m + 1 << endl;
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int x = -1;
    for (int i = 0; i < 7; ++i) {
        if ((1 << i) == n) {
            x = i;
            break;
        }
    }
    if (x != -1) {
        cout << n / 2 * x << endl;
        solve(0, n);
    } else {
        //cout << -1 << endl;
    }
    return 0;
}
