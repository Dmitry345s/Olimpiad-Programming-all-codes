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

Node* build(int l, int r) {
    Node* v = new Node();
    if (l + 1 == r) {
        v->val = 0;
        return v;
    }
    int m = (l + r) / 2;
    v->l = build(l, m);
    v->r = build(m, r);
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
    rt->val = rt->l->val + rt->r->val;
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

int get2(Node* v, int l, int r, int k) {
    //cout << l << " " << r << " " << v->val << " " << k << endl;
    if (v->val < k) {
        return -1;
    }
    if (l + 1 == r) {
        return l;
    }
    int m = (l + r) / 2;
    if (v->l->val >= k) {
        return get2(v->l, l, m, k);
    } else {
        return get2(v->r, m, r, k - v->l->val);
    }
}

signed main() {
    freopen("rollback.in", "r", stdin);
    freopen("rollback.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> mp;
    vector<Node*> trees(n + 1);
    trees[n] = build(0, n);
    for (int i = n - 1; i >= 0; --i) {
        if (mp.find(a[i]) == mp.end()) {
            trees[i] = update(trees[i + 1], 0, n, i, 1);
        } else {
            trees[i] = update(update(trees[i + 1], 0, n, mp[a[i]], 0), 0, n, i, 1);
        }
        mp[a[i]] = i;
    }
    int q;
    cin >> q;
    int p = 0;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        int l = (x + p) % n + 1, k = (y + p) % m + 1;
        l--;
        //cout << l << " " << k << endl;
        p = get2(trees[l], 0, n, k) + 1;
        cout << p << endl;
    }
    return 0;
}
