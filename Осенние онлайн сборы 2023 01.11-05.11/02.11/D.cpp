#include<bits/stdc++.h>

using namespace std;

int MAX = 5e5;
vector<int> k(MAX);
vector<int> tree(4 * MAX + 3);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = k[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }
    build(1, 0, n);
    if (n > 5000) {
        int q;
        cin >> q;
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int b = 1; b < n - 1; ++b) {
            int l = 0, r = n - b;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                int x = get(1, 0, n, max(b - m, 0), b) + get(1, 0, n, b + m, n), y = get(1, 0, n, max(b - m - 1, 0), b) + get(1, 0, n, b + m + 1, n);
                if (x - y < 0) {
                    l = m;
                } else {
                    r = m;
                }
            }
            ans = max(ans, k[b] + get(1, 0, n, max(b - r, 0), b) + get(1, 0, n, b + r, n));
        }
        cout << ans << endl;
        return 0;
    }
    vector<vector<int>> dp(n, vector<int> (n));
    for (int a = 0; a < n; ++a) {
        for (int c = a + 2; c < n; ++c) {
            int m = (a + c) / 2 + 1;
            int maxm = dp[a][c - 1] - k[a] - k[c - 1];
            if (m > (a + c - 1) / 2 + 1) {
                maxm = max(maxm, k[m - 1]);
            }
            dp[a][c] = k[a] + k[c] + maxm;
        }
    }
    vector<vector<int>> dp2(n, vector<int> (n));
    for (int l = n - 1; l >= 0; --l) {
        vector<int> pref(n);
        for (int r = 0; r < n; ++r) {
            if (r == 0) {
                pref[r] = dp[l][r];
            } else {
                pref[r] = max(pref[r - 1], dp[l][r]);
            }
            if (l == n - 1) {
                dp2[l][r] = pref[r];
            } else {
                dp2[l][r] = max(dp2[l + 1][r], pref[r]);
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << dp2[l][r] << endl;
    }
    return 0;
}
