#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct Node {
    int x, y, cnt;
    Node *l = nullptr, *r = nullptr;
    Node(int x1) {
        x = x1;
        y = rnd();
        cnt = 1;
    }
};

void upd(Node* rt) {
    int cnt = 1;
    if (rt->l != nullptr) {
        cnt += rt->l->cnt;
    }
    if (rt->r != nullptr) {
        cnt += rt->r->cnt;
    }
    rt->cnt = cnt;
}

pair<Node*, Node*> split_k(Node* rt, int k) {
    if (rt == nullptr) return {nullptr, nullptr};
    if (rt->cnt == k) return {rt, nullptr};
    if (k == 0) return {nullptr, rt};
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
        auto rt3 = merge(rt1, rt2->l);
        rt2->l = rt3;
        upd(rt2);
        return rt2;
    } else {
        auto rt3 = merge(rt1->r, rt2);
        rt1->r = rt3;
        upd(rt1);
        return rt1;
    }
}

void get_all(Node* rt) {
    if (rt->l != nullptr) {
        get_all(rt->l);
    }
    cout << rt->x << " ";
    if (rt->r != nullptr) {
        get_all(rt->r);
    }
}

Node* root = nullptr;

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        root = merge(root, new Node(i + 1));
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        auto [rt1, rt2] = split_k(root, l - 1);
        auto [rt3, rt4] = split_k(rt2, r - l + 1);
        root = merge(merge(rt3, rt1), rt4);
    }
    get_all(root);
    cout << endl;
    return 0;
}
