#include<bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int val;
    Node() {
        l = nullptr;
        r = nullptr;
        val = -1;
    }
};

Node* build1(Node* v, int l, int r) {
    if (l + 1 == r) {
        v->val = 1;
        return v;
    }
    int m = (l + r) / 2;
    v->l = build1(new Node(), l, m);
    v->r = build1(new Node(), m, r);
    return v;
}

Node* build2(Node* v, int l, int r) {
    if (l + 1 == r) {
        v->val = l;
        return v;
    }
    int m = (l + r) / 2;
    v->l = build2(new Node(), l, m);
    v->r = build2(new Node(), m, r);
    return v;
}

Node* update(Node* v, int l, int r, int in, int x) {
    Node *rt = new Node();
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
    return rt;
}

int get(Node* v, int l, int r, int in) {
    if (l + 1 == r) {
        return v->val;
    }
    int m = (l + r) / 2;
    if (in < m) {
        return get(v->l, l, m, in);
    } else {
        return get(v->r, m, r, in);
    }
}

int MAX = 1e5 + 5;
int n;
//vector<Node*> szs(MAX);
vector<Node*> ps(MAX);

int root(int v, int i) {
    int p = get(ps[i], 0, n, v);
    if (p == v) {
        return v;
    }
    int del = root(p, i);
    ps[i] = update(ps[i], 0, n, v, del);
    return del;
}

void unite(int v, int u, int i, int j) {
    int rv = root(v, i);
    int ru = root(u, i);
    //int szv = get(szs[i], 0, n, rv);
    //int szu = get(szs[i], 0, n, ru);
    ps[j] = update(ps[i], 0, n, ru, rv);
    //szs[j] = update(szs[i], 0, n, rv, szu + szv);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> n >> k;
    //szs[0] = new Node();
    //szs[0] = build1(szs[0], 0, n);
    ps[0] = new Node();
    ps[0] = build2(ps[0], 0, n);
    for (int j = 1; j <= k; ++j) {
        char t;
        cin >> t;
        if (t == '+') {
            int i, a, b;
            cin >> i >> a >> b;
            --a; --b;
            unite(a, b, i, j);
        } else {
            int i, a, b;
            cin >> i >> a >> b;
            --a; --b;
            if (root(a, i) == root(b, i)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
