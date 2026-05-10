#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("O3,Ofast")

using namespace std;

struct node {
    int sum, mn, mx;
};

int MAX = 2e5 + 5;
vector<int> a(MAX), update_tree(4 * MAX);
vector<node> tree(4 * MAX);

void build(int v, int & l, int & r) {
    if (l + 1 == r) {
        tree[v] = {a[l], a[l], a[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = {tree[2 * v + 1].sum + tree[2 * v + 2].sum, min(tree[2 * v + 1].mn, tree[2 * v + 2].mn), max(tree[2 * v + 1].mx, tree[2 * v + 2].mx)};
}

void push(int & v, int & l, int & r) {
    if (update_tree[v] == 0) return;
    int m = (l + r) / 2;
    int d = update_tree[v];
    tree[2 * v + 1] = {d * (m - l), d, d};
    tree[2 * v + 2] = {d * (r - m), d, d};
    update_tree[2 * v + 1] = d;
    update_tree[2 * v + 2] = d;
    update_tree[v] = 0;
}

void update(int v, int & l, int & r, int & left, int & right, int & x) {
    if (right <= l || r <= left) {
        return;
    }
    if (left <= l && r <= right) {
        tree[v] = {x * (r - l), x, x};
        update_tree[v] = x;
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, left, right, x);
    update(2 * v + 2, m, r, left, right, x);
    tree[v] = {tree[2 * v + 1].sum + tree[2 * v + 2].sum, min(tree[2 * v + 1].mn, tree[2 * v + 2].mn), max(tree[2 * v + 1].mx, tree[2 * v + 2].mx)};
}

int get(int v, int & l, int & r, int & left, int & right) {
    if (right <= l || r <= left) {
        return 0;
    }
    if (left <= l && r <= right) {
        return tree[v].sum;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    return get(2 * v + 1, l, m, left, right) + get(2 * v + 2, m, r, left, right);
}

int get2(int v, int & l, int & r, int & x) {
    if (l + 1 == r) {
        if (tree[v].mn > x) {
            return -1;
        }
        return l;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    if (tree[2 * v + 2].mn <= x) {
        return get2(2 * v + 2, m, r, x);
    }
    return get2(2 * v + 1, l, m, x);
}

int get3(int v, int & l, int & r, int x) {
    if (l + 1 == r) {
        if (tree[v].sum <= x) {
            return l;
        }
        return r;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    if (tree[2 * v + 2].sum <= x) {
        return get3(2 * v + 1, l, m, x - tree[2 * v + 2].sum);
    }
    return get3(2 * v + 2, m, r, x);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = n - 1; i >= 0; --i) {
        cin >> a[i];
    }
    int z = 0;
    build(0, z, n);
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            int j = n - k;
            int l = get2(0, z, n, x);
            if (j <= l) {
                l++;
                update(0, z, n, j, l, x);
            }
        } else {
            int k, x;
            cin >> k >> x;
            int j = min(n - k, get2(0, z, n, x));
            int ans = 0;
            while (j >= 0) {
                j++;
                int l = get3(0, z, n, x + get(0, z, n, j, n));
                x -= get(0, z, n, l, j);
                ans += (j - l);
                j = min(l - 1, get2(0, z, n, x));
            }
            /*while (j >= 0) {
                x -= get(0, 0, n, j, j + 1);
                j = min(j - 1, get2(0, 0, n, x));
                ans++;
            }*/
            cout << ans << '\n';
        }
    }
    return 0;
}
