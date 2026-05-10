#include<bits/stdc++.h>
#define int long long

using namespace std;

int MAX = 3e5;
vector<int> tree(4 * MAX);

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v + 1, l, m, id, x);
    } else {
        update(2 * v + 2, m, r, id, x);
    }
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int get(int v, int l, int r, int left, int right) {
    if (right <= l || r <= left) {
        return 0;
    }
    if (left <= l && r <= right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v + 1, l, m, left, right) + get(2 * v + 2, m, r, left, right);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int st = 0;
    for (int i = 0; i < n; ++i) {
        st += a[i] - get(0, 0, n, 0, a[i]);
        update(0, 0, n, a[i], 1);
    }
    cout << st << endl;
    for (int i = 0; i < n - 1; ++i) {
        st -= a[i];
        st += (n - 1 - a[i]);
        cout << st << endl;
    }
    return 0;
}
