#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> st(n, vector<int> (n));
    for (int l = 0; l < n; ++l) {
        int nmx = -INF;
        int now = l + 1;
        for (int r = l + 2; r < n; ++r) {
            int nowt = (l + r) / 2;
            while (now <= nowt) {
                nmx = max(nmx, a[now]);
                now++;
            }
            st[l][r] = nmx + a[l] + a[r];
        }
    }
    vector<vector<int>> ans(n, vector<int> (n));
    for (int d = 3; d <= n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = l + d - 1;
            if (r >= n) continue;
            ans[l][r] = max(st[l][r], max(ans[l + 1][r], ans[l][r - 1]));
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << ans[l][r] << endl;
    }
    return 0;
}
