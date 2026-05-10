#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1;
int tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree[v] += 1;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x);
    } else {
        update(2 * v + 1, m, r, in, x);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

int solve(vector<int> a, vector<int> b, int n) {
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[a[i]] = i;
    }
    build(1, 0, n);
    int now = 0;
    for (int i = n - 1; i >= 0; --i) {
        now += get(1, 0, n, 0, pos[b[i]]);
        update(1, 0, n, pos[b[i]], 1);
    }
    int ans = now;
    for (int i = n - 1; i >= 0; --i) {
        now -= (n - 1 - pos[b[i]]) - pos[b[i]];
        ans = min(ans, now);
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        --b[i];
    }
    cout << min(solve(a, b, n), solve(b, a, n)) << endl;
    return 0;
}
