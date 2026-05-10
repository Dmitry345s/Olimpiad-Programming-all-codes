#include<bits/stdc++.h>

using namespace std;

struct Node {
    int pr, sf, sm;
    Node(int x = 0) {
        pr = min(0, x);
        sf = min(0, x);
        sm = x;
    }
};

struct Node2 {
    int pr, sf, sm;
    Node2(int x = 0) {
        pr = max(0, x);
        sf = max(0, x);
        sm = x;
    }
};

Node operator + (Node a, Node b) {
    Node c;
    c.sm = a.sm + b.sm;
    c.pr = min(a.pr, a.sm + b.pr);
    c.sf = min(b.sf, b.sm + a.sf);
    return c;
}

Node2 operator + (Node2 a, Node2 b) {
    Node2 c;
    c.sm = a.sm + b.sm;
    c.pr = max(a.pr, a.sm + b.pr);
    c.sf = max(b.sf, b.sm + a.sf);
    return c;
}

int MAX = 5e5 + 5;
vector<Node> tree(4 * MAX);
vector<Node2> tree2(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = Node(1);
        tree2[v] = Node2(1);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int id, int num) {
    if (l + 1 == r) {
        tree[v] = Node(num);
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, num);
    } else {
        update(2 * v + 1, m, r, id, num);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

Node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return Node();
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

void update2(int v, int l, int r, int id, int num) {
    if (l + 1 == r) {
        tree2[v] = Node2(num);
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update2(2 * v, l, m, id, num);
    } else {
        update2(2 * v + 1, m, r, id, num);
    }
    tree2[v] = tree2[2 * v] + tree2[2 * v + 1];
}

Node2 get2(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return Node2();
    }
    if (ql <= l && r <= qr) {
        return tree2[v];
    }
    int m = (l + r) / 2;
    return get2(2 * v, l, m, ql, qr) + get2(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> tr(n + 1);
    for (int i = 0; i < n; ++i) {
        tr[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int)tr[i - 1].size(); ++j) {
            update(1, 0, n, tr[i - 1][j], -1);
        }
        int l = 0, r = 1;
    }
    return 0;
}
