#include<bits/stdc++.h>

using namespace std;

const int INF = 500000;

const int MAX = 2e5 + 1;
pair<int, int> tree[2][2 * MAX];

void build(int u, int n) {
    for (int i = n; i < 2 * n; ++i) tree[u][i] = {INF, i - n};
    for (int i = n - 1; i >= 0; --i) {
        tree[u][i] = min(tree[u][2 * i], tree[u][2 * i + 1]);
    }
}

void upd(int u, int n, int in, int x) {
    int v = in + n;
    tree[u][v].first = x;
    while (v > 1) {
        v /= 2;
        tree[u][v] = min(tree[u][2 * v], tree[u][2 * v + 1]);
    }
}

pair<int, int> get(int u, int n, int l, int r) {
    pair<int, int> ans = {INF, INF};
    l += n;
    r += n;
    while (l < r) {
        if (l % 2) {
            ans = min(ans, tree[u][l]);
            l += 1;
        }
        l /= 2;
        if (r % 2) {
            ans = min(ans, tree[u][r - 1]);
        }
        r /= 2;
    }
    return ans;
}

int nans[MAX];

int solve(vector<int> x, int n, int kl, int kr, int ml, int mr) {
    pair<int, int> seg[2];
    seg[0] = {kl, kr};
    seg[1] = {ml, mr};
    int ch[2][n];
    for (int i = 0; i < n - 1; ++i) {
        if (x[i + 1] - x[i] >= seg[0].first && x[i + 1] - x[i] <= seg[0].second) {
            ch[0][i] = 1;
        } else {
            ch[0][i] = 0;
        }
        if (x[i + 1] - x[i] >= seg[1].first && x[i + 1] - x[i] <= seg[1].second) {
            ch[1][i] = 1;
        } else {
            ch[1][i] = 0;
        }
    }
    int ls[2][n];
    ls[0][0] = 0;
    ls[1][0] = 0;
    for (int i = 1; i < n; ++i) {
        if (ch[0][i - 1]) {
            ls[0][i] = ls[0][i - 1];
        } else {
            ls[0][i] = i;
        }
        if (ch[1][i - 1]) {
            ls[1][i] = ls[1][i - 1];
        } else {
            ls[1][i] = i;
        }
    }
    build(0, n);
    build(1, n);
    vector<vector<int>> dp(2, vector<int>(n, INF));
    vector<vector<int>> p(2, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < 2; ++u) {
            if (ls[u][i] == 0) {
                //cout << i << " " << u << endl;
                dp[u][i] = i;
                upd(u, n, i, dp[u][i] - i - 1);
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int u = 0; u < 2; ++u) {
            int u2 = (u ^ 1);
            int gl = ls[u][i] - 1;
            int gr = i;
            if (i < n - 1) {
                int xx = x[i + 1];
                int jj = upper_bound(x.begin(), x.end(), xx - seg[u2].first) - x.begin() - 1;
                gr = min(gr, jj + 1);
                int jj2 = lower_bound(x.begin(), x.end(), xx - seg[u2].second) - x.begin();
                gl = max(gl, jj2);
            }
            gl = max(gl, 0);
            //cout << i << " " << u << " " << gl << " " << gr << endl;
            auto [ans1, ans2] = get(u2, n, gl, gr);
            if (ans1 + i < dp[u][i]) {
                dp[u][i] = ans1 + i;
                p[u][i] = ans2;
                upd(u, n, i, dp[u][i] - i - 1);
            }
        }
    }
    int v1 = 0, v2 = n - 1;
    int ans = dp[0][n - 1];
    if (dp[1][n - 1] < ans) {
        ans = dp[1][n - 1];
        v1 = 1;
        v2 = n - 1;
    }
    if (ans == INF) return ans;
    while (v2 >= 0) {
        int nv2 = p[v1][v2];
        for (int j = v2; j > nv2; --j) {
            nans[j] = v1;
        }
        v1 ^= 1;
        v2 = nv2;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    int s;
    cin >> s;
    int mn = n;
    int in = -1;
    vector<array<int, 4>> all;
    for (int i = 0; i < s; ++i) {
        int kl, kr, ml, mr;
        cin >> kl >> kr >> ml >> mr;
        all.push_back({kl, kr, ml, mr});
        int y = solve(x, n, kl, kr, ml, mr);
        if (y < mn) {
            mn = y;
            in = i;
        }
    }
    if (in == -1) {
        cout << 0 << endl;
        return 0;
    }
    auto [kl, kr, ml, mr] = all[in];
    mn = solve(x, n, kl, kr, ml, mr);
    cout << in + 1 << " " << mn << endl;
    for (int i = 0; i < n; ++i) {
        cout << nans[i] + 1;
    }
    cout << endl;
    return 0;
}
