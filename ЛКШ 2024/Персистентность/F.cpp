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

Node* update(Node* v, int l, int r, int in) {
    Node* rt = new Node();
    rt->l = v->l;
    rt->r = v->r;
    rt->val = v->val;
    if (l + 1 == r) {
        rt->val += 1;
        return rt;
    }
    int m = (l + r) / 2;
    if (in < m) {
        rt->l = update(rt->l, l, m, in);
    } else {
        rt->r = update(rt->r, m, r, in);
    }
    rt->val = rt->r->val + rt->l->val;
    return rt;
}

int get(Node* v1, Node* v2, int l, int r, int k) {
    //cout << l << " " << r << " " << v2->val << " " << v1->val << " " << k << endl;
    if (l + 1 == r) {
        return r - 1;
    }
    int m = (l + r) / 2;
    if (v2->l->val - v1->l->val >= k) {
        return get(v1->l, v2->l, l, m, k);
    }
    return get(v1->r, v2->r, m, r, k - (v2->l->val - v1->l->val));
}

signed main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n);
    int l, m;
    cin >> a[0] >> l >> m;
    vector<int> b;
    b.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        a[i] = (1ll * a[i - 1] * l + m) % ((int)1e9);
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int sz = (int)b.size();
    vector<Node*> trees(n + 1);
    trees[0] = build(0, sz);
    for (int i = 0; i < n; ++i) {
        int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        trees[i + 1] = update(trees[i], 0, sz, j);
    }
    int B;
    cin >> B;
    long long ans = 0;
    for (int _ = 0; _ < B; ++_) {
        int G;
        cin >> G;
        vector<int> x(G);
        vector<int> y(G);
        vector<int> i(G);
        vector<int> j(G);
        vector<int> k(G);
        int lx, mx, ly, my, lk, mk;
        cin >> x[0] >> lx >> mx;
        cin >> y[0] >> ly >> my;
        cin >> k[0] >> lk >> mk;
        i[0] = min(x[0], y[0]);
        j[0] = max(x[0], y[0]);
        ans += b[get(trees[i[0] - 1], trees[j[0]], 0, sz, k[0])];
        //cout << ans << endl;
        for (int i2 = 1; i2 < G; ++i2) {
            x[i2] = ((1ll * (i[i2 - 1] - 1) * lx + mx) % n) + 1;
            y[i2] = ((1ll * (j[i2 - 1] - 1) * ly + my) % n) + 1;
            i[i2] = min(x[i2], y[i2]);
            j[i2] = max(x[i2], y[i2]);
            k[i2] = ((1ll * (k[i2 - 1] - 1) * lk + mk) % (j[i2] - i[i2] + 1)) + 1;
            ans += b[get(trees[i[i2] - 1], trees[j[i2]], 0, sz, k[i2])];
        }
    }
    cout << ans << endl;
    return 0;
}
