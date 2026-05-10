#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")

using namespace std;

const int MAX = 12e4;
bitset<MAX> all[MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        all[i][i] = 1;
    }
    for (int i = 0; i < n + k - 1; ++i) {
        char c;
        cin >> c;
        if (c == 'S') {
            int a, b;
            cin >> a >> b;
            --a; --b;
            all[a] |= all[b];
            all[b] |= all[a];
        } else if (c == 'Q') {
            int v, d;
            cin >> v >> d;
            --v; --d;
            if (all[v][d]) {
                cout << "yes" << '\n';
            } else {
                cout << "no" << '\n';
            }
        } else {
            int v;
            cin >> v;
            --v;
            int ans = 0;
            for (int j = 0; j < n; ++j) {
                ans += all[j][v];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
