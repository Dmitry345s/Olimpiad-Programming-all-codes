#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct Node {
    int x, y, cnt, mn, ps;
    Node *l = nullptr, *r = nullptr;
    Node(int x1) {
        x = x1;
        y = rnd();
        cnt = 1;
        mn = x1;
        ps = 0;
    }
};

void push(Node* rt) {
    if (rt->ps == 1) {
        auto rt1 = rt->l;
        rt->l = rt->r;
        rt->r = rt1;
        if (rt->l != nullptr) {
            rt->l->ps ^= 1;
        }
        if (rt->r != nullptr) {
            rt->r->ps ^= 1;
        }
    }
    rt->ps = 0;
}

void upd(Node* rt) {
    int cnt = 1, mn = rt->x;
    if (rt->l != nullptr) {
        cnt += rt->l->cnt;
        mn = min(rt->l->mn, mn);
    }
    if (rt->r != nullptr) {
        cnt += rt->r->cnt;
        mn = min(rt->r->mn, mn);
    }
    rt->cnt = cnt;
    rt->mn = mn;
}

pair<Node*, Node*> split_k(Node* rt, int k) {
    if (rt == nullptr) return {nullptr, nullptr};
    push(rt);
    if (k == 0) return {nullptr, rt};
    if (rt->cnt == k) return {rt, nullptr};
    if (rt->l != nullptr) {
        if (rt->l->cnt >= k) {
            auto [rt1, rt2] = split_k(rt->l, k);
            rt->l = rt2;
            upd(rt);
            return {rt1, rt};
        } else {
            auto [rt1, rt2] = split_k(rt->r, k - rt->l->cnt - 1);
            rt->r = rt1;
            upd(rt);
            return {rt, rt2};
        }
    } else {
        auto [rt1, rt2] = split_k(rt->r, k - 1);
        rt->r = rt1;
        upd(rt);
        return {rt, rt2};
    }
}

Node* merge(Node* rt1, Node* rt2) {
    if (rt1 == nullptr) return rt2;
    if (rt2 == nullptr) return rt1;
    if (rt1->y < rt2->y) {
        push(rt2);
        auto rt3 = merge(rt1, rt2->l);
        rt2->l = rt3;
        upd(rt2);
        return rt2;
    } else {
        push(rt1);
        auto rt3 = merge(rt1->r, rt2);
        rt1->r = rt3;
        upd(rt1);
        return rt1;
    }
}

Node* root = nullptr;

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        root = merge(root, new Node(a));
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        int l, r;
        cin >> l >> r;
        auto [rt1, rt2] = split_k(root, r);
        auto [rt3, rt4] = split_k(rt1, l - 1);
        if (t == 1) {
            rt4->ps ^= 1;
        } else {
            cout << rt4->mn << endl;
        }
        root = merge(merge(rt3, rt4), rt2);
    }
    return 0;
}
