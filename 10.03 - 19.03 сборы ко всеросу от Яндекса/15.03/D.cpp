#include<bits/stdc++.h>

#pragma GCC optmize("O3")
#pragma GCC optmize("unroll-loops")

using namespace std;
using ull = unsigned long long;

const int INF = 2e9 + 1;
const int MAX = 5, MAXN = 1e5 + 1;
vector<ull> tree[4 * MAXN];
vector<ull> all[2][MAXN];
pair<int, vector<int>> a[MAXN];
ull P = 1791791791;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        for (int b = 0; b < 2; ++b) {
            for (ull a : all[b][l]) {
                tree[v].push_back(a);
            }
        }
        sort(tree[v].begin(), tree[v].end());
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    for (auto x : tree[2 * v]) {
        tree[v].push_back(x);
    }
    for (auto x : tree[2 * v + 1]) {
        tree[v].push_back(x);
    }
    sort(tree[v].begin(), tree[v].end());
}

int get(int v, int in) {
    int ans = 0;
    for (ull a : all[0][in]) {
        ans += upper_bound(tree[v].begin(), tree[v].end(), a) - lower_bound(tree[v].begin(), tree[v].end(), a);
    }
    for (ull a : all[1][in]) {
        ans -= upper_bound(tree[v].begin(), tree[v].end(), a) - lower_bound(tree[v].begin(), tree[v].end(), a);
    }
    return ans;
}

int fid(int v, int l, int r, int in) {
    if (l + 1 == r) {
        return l;
    }
    int m = (l + r) / 2;
    int p = get(2 * v, in);
    if (p == 0) return l;
    if (p < m - l) {
        return fid(2 * v, l, m, in);
    }
    return fid(2 * v + 1, m, r, in);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        a[i].second.assign(m, 0);
        for (int j = 0; j < m; ++j) {
            cin >> a[i].second[j];
        }
        sort(a[i].second.begin(), a[i].second.end());
        cin >> a[i].first;
    }
    sort(a, a + n);
    for (int i = 0; i < n; ++i) {
        for (int mask = 1; mask < (1 << m); ++mask) {
            ull h1 = 0;
            int cnt = 0;
            for (int j = 0; j < m; ++j) {
                if ((mask >> j) & 1) {
                    h1 *= P;
                    h1 += a[i].second[j];
                    cnt++;
                }
            }
            all[(cnt - 1) % 2][i].push_back(h1);
        }
    }
    build(1, 0, n);
    int ans = INF;
    int c2 = 100000;
    int c = 20000 * (n >= c2) + (n - 1) * (n < c2);
    for (int i = 0; i < min(n - 1, c); ++i) {
        if (get(1, i) != n && a[i].first + a[i + 1].first < ans) {
            int j = fid(1, 0, n, i);
            ans = min(ans, a[i].first + a[j].first);
        }
    }
    if (c == n - 1) {
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
        return 0;
    }
    for (int i = max(n / 2 - c, 0); i < min(n - 1, n / 2 + c / 2); ++i) {
        if (get(1, i) != n && a[i].first + a[i + 1].first < ans) {
            int j = fid(1, 0, n, i);
            ans = min(ans, a[i].first + a[j].first);
        }
    }
    for (int i = max(0, n - c); i < n - 1; ++i) {
        if (get(1, i) != n && a[i].first + a[i + 1].first < ans) {
            int j = fid(1, 0, n, i);
            ans = min(ans, a[i].first + a[j].first);
        }
    }
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
