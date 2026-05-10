#include<bits/stdc++.h>

using namespace std;

vector<int> tree(4e5, 0);
vector<int> a(1e5);

void update(int l, int r, int v, int i, int x) {
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (i < m) {
            update(l, m, 2 * v, i, x);
        } else {
            update(m, r, 2 * v + 1, i, x);
        }
        tree[v] = __gcd(tree[2 * v], tree[2 * v + 1]);
    } else {
        tree[v] = x;
    }
}

int get_gcd(int l, int r, int left, int right, int v) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (left >= m) {
        return get_gcd(m, r, left, right, 2 * v + 1);
    } else if (right <= m) {
        return get_gcd(l, m, left, right, 2 * v);
    } else {
        return __gcd(get_gcd(l, m, left, m, 2 * v), get_gcd(m, r, m, right, 2 * v + 1));
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        update(0, n, 1, i, a[i]);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char p;
        cin >> p;
        if (p == 'u') {
            int j, x;
            cin >> j >> x;
            update(0, n, 1, j - 1, x);
        } else {
            int left, right;
            cin >> left >> right;
            cout << get_gcd(0, n, left - 1, right, 1) << '\n';
        }
    }
    return 0;
}
