#include<iostream>
#include<vector>

using namespace std;

vector<int> tree(8e5, 0);
int n;

void update(int l, int r, int v, int i, int x) {
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (i < m) {
            update(l, m, 2 * v, i, x);
        } else {
            update(m, r, 2 * v + 1, i, x);
        }
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    } else {
        if (x == 0) {
            tree[v] = 1;
        } else {
            tree[v] = 0;
        }
    }
}

int get_cnt(int l, int r, int left, int right, int v) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_cnt(l, m, left, right, 2 * v);
    } else if (left >= m) {
        return get_cnt(m, r, left, right, 2 * v + 1);
    } else {
        return get_cnt(l, m, left, m, 2 * v) + get_cnt(m, r, m, right, 2 * v + 1);
    }
}

int get_ans(int l, int r, int k) {
    int p = get_cnt(0, n, l, r, 1);
    if (p < k) {
        return -2;
    }
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int check = get_cnt(0, n, l, m, 1);
        if (check >= k) {
            r = m;
        } else {
            l = m;
            k -= check;
        }
    }
    return l;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        update(0, n, 1, i, x);
    }
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
        char p;
        cin >> p;
        if (p == 'u') {
            int i, x;
            cin >> i >> x;
            update(0, n, 1, i - 1, x);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            cout << get_ans(l - 1, r, k) + 1 << '\n';
        }
    }
    return 0;
}
