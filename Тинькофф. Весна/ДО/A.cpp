#include<iostream>
#include<vector>

using namespace std;

vector<int> tree(4e5, -1);
vector<int> a(1e5);

void update(int l, int r, int v, int i, int x) {
    if (l == r - 1) {
        tree[v] = i;
    } else {
        int m = (l + r) / 2;
        if (i < m) {
            update(l, m, 2 * v, i, x);
        } else {
            update(m, r, 2 * v + 1, i, x);
        }
        if (a[tree[2 * v]] >= a[tree[2 * v + 1]]) {
            tree[v] = tree[2 * v];
        } else {
            tree[v] = tree[2 * v + 1];
        }
    }
}

int get_max(int l, int r, int left, int right, int v) {
    if ((l == r - 1) || (l == left && r == right)) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (left < m && right > m) {
        int k = get_max(l, m, left, m, 2 * v);
        int d = get_max(m, r, m, right, 2 * v + 1);
        if (a[k] >= a[d]) {
            return k;
        }
        return d;
    } else if (right <= m) {
        return get_max(l, m, left, right, 2 * v);
    } else if (left >= m) {
        return get_max(m, r, left, right, 2 * v + 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        update(0, n, 1, i, a[i]);
    }
    int m;
    cin >> m;
    int l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        cout << get_max(0, n, l - 1, r, 1) + 1 << '\n';
    }
    return 0;
}
