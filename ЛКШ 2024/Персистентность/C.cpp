#include<bits/stdc++.h>

using namespace std;

struct Node {
    int l, r, val;
    Node *ls, *rs;
    Node() {
        l = -1;
        r = -1;
        ls = nullptr;
        rs = nullptr;
        val = -1;
    }
};

int MAX = 2e5;
vector<int> a(MAX);

Node* build(Node* now, int l, int r) {
    now->l = l;
    now->r = r;
    if (l + 1 == r) {
        now->val = a[l];
        return now;
    }
    int m = (l + r) / 2;
    now->ls = build(new Node(), l, m);
    now->rs = build(new Node(), m, r);
    return now;
}

int get(Node* v, int in) {
    if (v->l + 1 == v->r) {
        return v->val;
    }
    int m = (v->l + v->r) / 2;
    if (in < m) {
        return get(v->ls, in);
    } else {
        return get(v->rs, in);
    }
}

Node* update(Node* v, int in, int x) {
    Node *r = new Node();
    r->l = v->l;
    r->r = v->r;
    r->ls = v->ls;
    r->rs = v->rs;
    r->val = v->val;
    if (r->l + 1 == r->r) {
        r->val = x;
        return r;
    }
    int m = (r->l + r->r) / 2;
    if (in < m) {
        r->ls = update(r->ls, in, x);
    } else {
        r->rs = update(r->rs, in, x);
    }
    return r;
}

signed main() {
    int n;
    cin >> n;
    Node* rt = new Node();
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    rt = build(rt, 0, n);
    vector<Node*> all(1);
    all[0] = rt;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string t;
        cin >> t;
        if (t == "create") {
            int tm, in, x;
            cin >> tm >> in >> x;
            tm--;
            in--;
            all.push_back(update(all[tm], in, x));
        } else {
            int tm, in;
            cin >> tm >> in;
            tm--;
            in--;
            cout << get(all[tm], in) << endl;
        }
    }
    return 0;
}
