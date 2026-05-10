#include<bits/stdc++.h>

#define double long double
#define int long long

using namespace std;

int MAX = 1e5 + 1;
vector<int> pref(MAX);
vector<int> dp(MAX);
vector<int> tree(4 * (MAX + 1));

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = -1e5;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return -1e5;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

bool ch(vector<double> a, double x, int k, int m) {
    int n = (int)a.size();
    dp.assign(n + 1, -1e5);
    for (int i = 0; i < n; ++i) {
        a[i] -= x;
    }
    vector<double> b(n);
    b[0] = a[0];
    vector<pair<double, int>> bs;
    bs.push_back({b[0], 0});
    for (int i = 1; i < n; ++i) {
        b[i] = b[i - 1] + a[i];
        bs.push_back({b[i], i});
    }
    sort(bs.begin(), bs.end());
    build(1, 0, n + 1);
    for (int i = 0; i < n; ++i) {
        int l = bs[i].second + 1 - m;
        if (bs[i].first >= 0) {
            update(1, 0, n + 1, 0, 0);
            dp[0] = 0;
        }
        //cout << x << " " << bs[i].first << " " << bs[i].second << " " << l << endl;
        if (l + 1 >= 1) {
            dp[bs[i].second + 1] = max(get(1, 0, n + 1, 0, l + 1) + 1, dp[bs[i].second + 1]);
        }
        update(1, 0, n + 1, bs[i].second + 1, dp[bs[i].second + 1]);
    }
    return dp.back() >= k;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<double> a(n);
    //int minm = 1e9 + 1, maxm = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    double l = 0, r = 1e9 + 1;
    double EPS = 1e-7;
    while (l + EPS < r) {
        double c = (l + r) / 2;
        //cout << l << " " << r << endl;
        if (ch(a, c, k, m)) {
            l = c;
        } else {
            r = c;
        }
    }
    double x = l;
    //cout << x << endl;
    dp.assign(n, -1e5);
    vector<int> p(n, 0);
    for (int i = m - 1; i < (int)a.size(); ++i) {
        if (pref[i + 1] / (double)(i + 1) >= x) {
            dp[i] = 1;
            p[i] = i + 1;
        }
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int t = 0; t <= i - m; ++t) {
            if ((pref[i + 1] - pref[t + 1]) / (double)(i - t) >= x) {
                if (dp[i] <= dp[t] + 1) {
                    dp[i] = dp[t] + 1;
                    p[i] = i - t;
                }
            }
        }
        //cout << i << " " << dp[i] << " " << p[i] << endl;
    }
    vector<int> ans;
    int now = n - 1;
    int now2 = dp.back();
    while (now2 > 0) {
        ans.push_back(p[now]);
        now -= p[now];
        now2 -= 1;
    }
    reverse(ans.begin(), ans.end());
    while (ans.size() > k) {
        ans[k - 1] += ans.back();
        ans.pop_back();
    }
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
