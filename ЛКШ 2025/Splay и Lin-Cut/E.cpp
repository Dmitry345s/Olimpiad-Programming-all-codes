#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 2;

struct Node {
    int ss[2];
    int p, pth;
    int rev, sz;
    Node() {
        ss[0] = -1;
        ss[1] = -1;
        pth = -1;
        p = -1;
        rev = 0;
        sz = 1;
    }
};

vector<Node> tree;
int n;

int dir(int v) {
    if (tree[v].p == -1) return -1;
    if (v == tree[tree[v].p].ss[0]) return 0;
    return 1;
}

void upd(int v) {
    if (v == -1) return;
    tree[v].sz = 1;
    for (int i = 0; i < 2; ++i) {
        if (tree[v].ss[i] != -1) {
            tree[v].sz += tree[tree[v].ss[i]].sz;
        }
    }
}

void push(int v) {
    if (v == -1) return;
    int x = tree[v].rev;
    tree[v].rev = 0;
    if (x) {
        swap(tree[v].ss[0], tree[v].ss[1]);
    }
    int ls = tree[v].ss[0], rs = tree[v].ss[1];
    if (ls != -1) {
        tree[ls].rev ^= x;
    }
    if (rs != -1) {
        tree[rs].rev ^= x;
    }
}

void zig(int v) {
    swap(tree[v].pth, tree[tree[v].p].pth);
    int y = dir(v);
    int pr = dir(tree[v].p);
    int p = tree[v].p;
    int g = tree[p].p;
    int b = tree[v].ss[(y ^ 1)];
    if (g != -1) {
        tree[g].ss[pr] = v;
    }
    tree[v].p = g;
    tree[v].ss[(y ^ 1)] = p;
    tree[p].p = v;
    tree[p].ss[y] = b;
    if (b != -1) tree[b].p = p;
    upd(p);
    upd(v);
    upd(g);
}

void zigzig(int v) {
    zig(tree[v].p);
    zig(v);
}

void zigzag(int v) {
    zig(v);
    zig(v);
}

void splay(int v) {
    while (tree[v].p != -1) {
        int g = tree[tree[v].p].p;
        push(g);
        push(tree[v].p);
        push(v);
        if (g == -1) {
            zig(v);
        } else if (dir(v) == dir(tree[v].p)) {
            zigzig(v);
        } else {
            zigzag(v);
        }
    }
    push(v);
}

void expose(int v) {
    splay(v);
    while (tree[v].pth != -1) {
        int p = tree[v].pth;
        splay(p);
        int y = tree[p].ss[1];
        if (y != -1) {
            tree[y].p = -1;
            tree[y].pth = p;
        }
        tree[p].ss[1] = v;
        tree[v].pth = -1;
        tree[v].p = p;
        upd(p);
        splay(v);
    }
}

void ch_root(int v) {
    if (v == -1) return;
    expose(v);
    int y = tree[v].ss[1];
    if (y != -1) {
        tree[y].p = -1;
        tree[y].pth = v;
        tree[v].ss[1] = -1;
        upd(v);
    }
    tree[v].rev ^= 1;
}

void link(int u, int v) {
    ch_root(u);
    tree[u].pth = v;
}

void cut(int u, int v) {
    ch_root(u);
    expose(v);
    tree[u].p = -1;
    tree[u].pth = -1;
    tree[v].ss[0] = -1;
    upd(v);
}

int get(int u, int v) {
    if (u == v) return 1;
    ch_root(u);
    expose(v);
    if (tree[u].p == -1) return 0;
    return 1;
}

signed main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        tree.push_back(Node());
    }
    for (int i = 0; i < m; ++i) {
        string t;
        cin >> t;
        int u, v;
        cin >> u >> v;
        --u; --v;
        if (t == "link") {
            link(u, v);
        } else if (t == "cut") {
            cut(u, v);
        } else {
            cout << get(u, v);
        }
    }
    return 0;
}
