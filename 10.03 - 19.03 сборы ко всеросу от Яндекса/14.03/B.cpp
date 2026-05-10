#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 1;
vector<int> tree[4 * MAX];
vector<pair<int, int>> ts;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {ts[l].second};
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

const int INF = 2e9;

int get1(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return -INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v].back();
    }
    int m = (l + r) / 2;
    return max(get1(2 * v, l,  m, ql, qr), get1(2 * v + 1, m, r, ql, qr));
}

int get2(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return (int)tree[v].size() - (upper_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin());
    }
    int m = (l + r) / 2;
    return get2(2 * v, l,  m, ql, qr, x) + get2(2 * v + 1, m, r, ql, qr, x);
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < k; ++i) {
        int tr;
        cin >> tr;
        ts.push_back({tr, i});
    }
    sort(ts.begin(), ts.end());
    for (auto [tr, i] : ts) {
        //cout << tr << " " << i << endl;
    }
    //cout << endl;
    build(1, 0, k);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] >= b[i]) {
            int j = upper_bound(ts.begin(), ts.end(), pair<int, int>{a[i], -1}) - ts.begin();
            int j2 = upper_bound(ts.begin(), ts.end(), pair<int, int>{b[i], -1}) - ts.begin();
            int ans = -1;
            if (j != j2) {
                ans = get1(1, 0, k, j2, j);
            }
            int cnt = 0;
            if (j != k) {
                cnt = get2(1, 0, k, j, k, ans);
                cnt %= 2;
            }
            //cout << i << " " << j << " " << j2 << " " << ans << " " << cnt << endl;
            if (cnt == 0) {
                sum += a[i];
            } else {
                sum += b[i];
            }
        } else {
            int j = upper_bound(ts.begin(), ts.end(), pair<int, int>{b[i], -1}) - ts.begin();
            int j2 = upper_bound(ts.begin(), ts.end(), pair<int, int>{a[i], -1}) - ts.begin();
            int ans = -1;
            if (j != j2) {
                ans = get1(1, 0, k, j2, j);
            }
            int cnt = 0;
            if (j != k) {
                cnt = get2(1, 0, k, j, k, ans);
                cnt %= 2;
            }
            if (cnt == 0) {
                if (ans == -1) {
                    sum += a[i];
                } else {
                    sum += b[i];
                }
            } else {
                if (ans == -1) {
                    sum += b[i];
                } else {
                    sum += a[i];
                }
            }
        }
    }
    cout << sum << endl;
    return 0;
}
