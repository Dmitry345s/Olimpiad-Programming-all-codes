#include<bits/stdc++.h>

using namespace std;

int MAX = 5e5;
vector<int> c;
vector<int> tree(4 * MAX);

void update(int v, int l, int r, int id) {
    if (l + 1 == r) {
        tree[v] += 1;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id);
    } else {
        update(2 * v + 1, m, r, id);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    vector<array<int, 4>> a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.push_back({y, 0, x, (int)1e9});
        c.push_back(x);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a.push_back({y1, -(i + n), x1, x2});
        a.push_back({y2, (i + n), x1, x2});
        c.push_back(x1);
        c.push_back(x2);
    }
    sort(a.begin(), a.end());
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    int k = c.size();
    vector<int> ans(m);
    for (int i = 0; i < (int) a.size(); ++i) {
        if (a[i][3] == 1e9) {
            int id = lower_bound(c.begin(), c.end(), a[i][2]) - c.begin();
            update(1, 0, k, id);
            continue;
        }
        int l = lower_bound(c.begin(), c.end(), a[i][2]) - c.begin();
        int r = lower_bound(c.begin(), c.end(), a[i][3]) - c.begin();
        int ch = get(1, 0, k, l, r + 1);
        if (a[i][1] < 0) {
            ans[-a[i][1] - n] = ch;
        } else {
            ans[a[i][1] - n] = ch - ans[a[i][1] - n];
        }
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
