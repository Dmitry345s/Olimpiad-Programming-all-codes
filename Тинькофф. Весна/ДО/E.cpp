#include<iostream>
#include<vector>

using namespace std;

vector<int> tree(8e5, -1e9);
int n;

void update(int l, int r, int v, int i, int x) {
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (i < m) {
            update(l, m, 2 * v, i, x);
        } else {
            update(m, r, 2 * v + 1, i, x);
        }
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    } else {
        tree[v] = x;
    }
}

int get_max(int l, int r, int left, int right, int v) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_max(l, m, left, right, 2 * v);
    } else if (left >= m) {
        return get_max(m, r, left, right, 2 * v + 1);
    } else {
        return max(get_max(l, m, left, m, 2 * v), get_max(m, r, m, right, 2 * v + 1));
    }
}

int get_ans(int i, int x) {
    int p = get_max(0, n, i, n, 1);
    if (p < x) {
        return -2;
    }
    int l = i, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int check = get_max(0, n, l, m, 1);
        if (check >= x) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}

int main() {
    cin >> n;
    int m;
    cin >> m;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        update(0, n, 1, i, x);
    }
    for (int j = 0; j < m; ++j) {
        int p, i, x;
        cin >> p >> i >> x;
        if (p == 0) {
            update(0, n, 1, i - 1, x);
        } else {
            cout << get_ans(i - 1, x) + 1 << '\n';
        }
    }
    return 0;
}
