#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;
pair<int, int> tree[2 * MAX];

void build(int n, vector<int> a) {
    for (int i = n; i < 2 * n; ++i) {
        tree[i] = {a[i - n], i - n};
    }
    for (int i = n - 1; i >= 0; --i) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }
}

void upd(int n, int in, int x) {
    int v = in + n;
    tree[v].first = max(tree[v].first - x, 0);
    while (v > 1) {
        v /= 2;
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
}

const int INF = 2e9;

pair<int, int> get(int n, int l, int r) {
    l += n;
    r += n;
    pair<int, int> ans = {INF, INF};
    while (l < r) {
        if (l % 2) {
            ans = min(ans, tree[l]);
            l += 1;
        }
        if (r % 2) {
            ans = min(ans, tree[r - 1]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

vector<pair<int, int>> ans;
int sum = 0;

void solve(int l, int r, int n) {
    if (l >= r) return;
    auto [mn, in] = get(n, l, r);
    auto [mn2, in2] = get(n, in + 1, r);
    if (mn2 == mn && in == 0) {
        in = in2;
    }
    //cout << l << " " << r << " " << in << endl;
    //cout << l << " " << r << " " << mn << " " << in << endl;
    ans.push_back({in, mn});
    sum += mn;
    for (int j = max(0, in - 1); j <= min(n - 1, in + 1); ++j) {
        upd(n, j, mn);
    }
    solve(l, in, n);
    solve(in + 1, r, n);
}

signed main() {
    int _, m;
    cin >> _ >> m;
    while(_--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        build(n, a);
        ans.clear();
        sum = 0;
        solve(0, n, n);
        cout << sum << endl;
        if (m > 0) {
            cout << (int)ans.size() << endl;
            for (auto [u, v] : ans) {
                cout << u + 1 << " " << v << endl;
            }
        }
    }
    return 0;
}
