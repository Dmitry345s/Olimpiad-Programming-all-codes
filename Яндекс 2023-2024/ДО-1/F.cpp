#include<bits/stdc++.h>

using namespace std;

int MAX = 1e6;
vector<int> tree(4 * MAX);

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] += 1;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
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
    ios::sync_with_stdio(0);
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
    vector<int> ch(n);
    for (int i = 0; i < n; ++i) {
        int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        ch[i] = get(1, 0, n, j + 1, n);
        update(1, 0, n, j, 1);
    }
    tree.assign(4 * MAX, 0);
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        int k = get(1, 0, n, 0, j);
        update(1, 0, n, j, 1);
        ans += 1ll * ch[i] * k;
    }
    cout << ans << endl;
    return 0;
}
