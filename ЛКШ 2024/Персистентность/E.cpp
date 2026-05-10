#include<bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int val;
    Node() {
        l = nullptr;
        r = nullptr;
        val = 0;
    }
};

Node* build(Node* v, int l, int r) {
    if (l + 1 == r) {
        v->val = 0;
        return v;
    }
    int m = (l + r) / 2;
    v->l = build(new Node(), l, m);
    v->r = build(new Node(), m, r);
    v->val = v->l->val + v->r->val;
    return v;
}

Node* update(Node* v, int l, int r, int in, int x) {
    Node* rt = new Node();
    rt->l = v->l;
    rt->r = v->r;
    rt->val = v->val;
    if (l + 1 == r) {
        rt->val = x;
        return rt;
    }
    int m = (l + r) / 2;
    if (in < m) {
        rt->l = update(rt->l, l, m, in, x);
    } else {
        rt->r = update(rt->r, m, r, in, x);
    }
    rt->val = rt->r->val + rt->l->val;
    return rt;
}

int get(Node* v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return v->val;
    }
    int m = (l + r) / 2;
    return get(v->l, l, m, ql, qr) + get(v->r, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<Node*> trees(n + 1);
    trees[0] = new Node();
    trees[0] = build(trees[0], 0, n);
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        trees[i + 1] = new Node();
        if (mp.find(a[i]) == mp.end()) {
            trees[i + 1] = update(trees[i], 0, n, i, 1);
        } else {
            trees[i + 1] = update(update(trees[i], 0, n, mp[a[i]], 0), 0, n, i, 1);
        }
        mp[a[i]] = i;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << get(trees[r], 0, n, l, r) << endl;
    }
    return 0;
}
