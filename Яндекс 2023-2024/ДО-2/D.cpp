#include<bits/stdc++.h>

using namespace std;

struct node {
    int mn, cnt, ans;
    node() {
        mn = 1e9;
        cnt = 0;
        ans = 0;
    }
};

node operator + (node a, node b) {
    node c;
    if (a.mn < b.mn) {
        c = a;
    } else if (b.mn < a.mn) {
        c = b;
    } else {
        c.mn = a.mn;
        c.cnt = a.cnt + b.cnt;
        c.ans = a.ans + b.ans;
    }
    return c;
}

int MAX = 2e5;
vector<node> tree(4 * MAX);
vector<int> c, update_tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v].mn = 0;
        tree[v].cnt = (c[r] - c[l]);
        tree[v].ans = c[r] - c[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void push(int v) {
    tree[2 * v].mn += update_tree[v];
    tree[2 * v + 1].mn += update_tree[v];
    update_tree[2 * v] += update_tree[v];
    update_tree[2 * v + 1] += update_tree[v];
    update_tree[v] = 0;
    if (tree[2 * v].mn != 0) {
        tree[2 * v].ans = 0;
    } else {
        tree[2 * v].ans = tree[2 * v].cnt;
    }
    if (tree[2 * v + 1].mn != 0) {
        tree[2 * v + 1].ans = 0;
    } else {
        tree[2 * v + 1].ans = tree[2 * v + 1].cnt;
    }
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].mn += x;
        update_tree[v] += x;
        if (tree[v].mn != 0) {
            tree[v].ans = 0;
        } else {
            tree[v].ans = tree[v].cnt;
        }
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return node();
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<array<int, 4>> b;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        b.push_back({y1, x1, x2, 1});
        b.push_back({y2, x1, x2, -1});
        c.push_back(x1);
        c.push_back(x2);
    }
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    int k = c.size() - 1;
    build(1, 0, k);
    int last = b[0][0];
    long long ans = 0;
    for (int i = 0; i < (int)b.size(); ++i) {
        int l = lower_bound(c.begin(), c.end(), b[i][1]) - c.begin();
        int r = lower_bound(c.begin(), c.end(), b[i][2]) - c.begin();
        ans += 1ll * (b[i][0] - last) * (c.back() - c[0] - get(1, 0, k, 0, k).ans);
        update(1, 0, k, l, r, b[i][3]);
        last = b[i][0];
    }
    cout << ans << endl;
    return 0;
}
