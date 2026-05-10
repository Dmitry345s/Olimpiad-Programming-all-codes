#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops","Ofast")

#define int long long

using namespace std;

const int MAX = 1e5 + 1, INF = 2e9;
int tree[4 * 2 * MAX];
int update_tree[4 * 2 * MAX];

void push(int v, int l, int r) {
    int m = (l + r) / 2;
    int x = update_tree[v];
    if (x == -INF) {
        update_tree[2 * v] = -INF;
        update_tree[2 * v + 1] = -INF;
        tree[2 * v] = 0;
        tree[2 * v + 1] = 0;
        update_tree[v] = 0;
        return;
    } else if (x < 0) {
        int y = (INF + x);
        update_tree[2 * v] = x;
        update_tree[2 * v + 1] = x;
        tree[2 * v] = (m - l) * y;
        tree[2 * v + 1] = (r - m) * y;
        update_tree[v] = 0;
        return;
    }
    update_tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
    tree[2 * v] += (m - l) * x;
    tree[2 * v + 1] += (r - m) * x;
    update_tree[v] = 0;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (ql == qr) return;
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        if (x != -INF) {
            update_tree[v] += x;
            tree[v] += (r - l) * x;
        }
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) return 0;
    if (ql <= l && r <= qr) return tree[v];
    push(v, l, r);
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

long long solve(int l, int r, vector<int>& x) {
    if ((int)x.size() == 0) return 0;
    int m = (l + r) / 2;
    if (l + 1 == r) {
        return (int)x.size();
    }
    vector<int> xl, xr;
    for (int i = 0; i < (int)x.size(); ++i) {
        if (x[i] < m) {
            xl.push_back(x[i]);
        } else {
            xr.push_back(x[i]);
        }
    }
    long long ans = solve(l, m, xl) + solve(m, r, xr);
    reverse(xl.begin(), xl.end());
    xl.push_back(l - 1);
    xr.push_back(r);
    int cnt = 1;
    update(1, 0, 2 * MAX, cnt + MAX, cnt + MAX + xr[0] - m, 1);
    for (int i = 0; i < (int)xr.size() - 1; ++i) {
        cnt = xr[i] - m + 1 - 2 * (i + 1);
        update(1, 0, 2 * MAX, cnt + MAX, cnt + MAX + xr[i + 1] - xr[i], 1);
    }
    for (int i = 0; i < (int)xl.size() - 1; ++i) {
        cnt = 2 * (i + 1) - (m - xl[i]);
        int now = xl[i];
        while (cnt > 0 && now > xl[i + 1]) {
            ans += get(1, 0, 2 * MAX, 0, cnt + MAX);
            now -= 1;
            cnt -= 1;
        }
    }
    tree[1] = 0;
    update_tree[1] = -INF;
    cnt = 1;
    update(1, 0, 2 * MAX, cnt + MAX, cnt + MAX + m - xl[0] - 1, 1);
    for (int i = 0; i < (int)xl.size() - 1; ++i) {
        cnt = m - xl[i] - 2 * (i + 1);
        update(1, 0, 2 * MAX, cnt + MAX, cnt + MAX + xl[i] - xl[i + 1], 1);
    }
    for (int i = 0; i < (int)xr.size() - 1; ++i) {
        cnt = 2 * (i + 1) - (xr[i] - m + 1);
        int now = xr[i];
        while (cnt > 0 && now < xr[i + 1]) {
            ans += get(1, 0, 2 * MAX, MAX, cnt + MAX);
            now += 1;
            cnt -= 1;
        }
    }
    tree[1] = 0;
    update_tree[1] = -INF;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<vector<int>> all(n);
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        all[a[i]].push_back(i);
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if ((int)all[i].size() == 0) continue;
        ans += solve(0, n, all[i]);
    }
    cout << ans << endl;
    return 0;
}
