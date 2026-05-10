#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct Node {
    int x, y, cnt, mx;
    Node *l = nullptr, *r = nullptr;
    Node(int x1) {
        x = x1;
        y = rnd();
        cnt = 1;
        mx = x1;
    }
};

void upd(Node* rt) {
    int cnt = 1, mx = rt->x;
    if (rt->l != nullptr) {
        cnt += rt->l->cnt;
        mx = max(rt->l->mx, mx);
    }
    if (rt->r != nullptr) {
        cnt += rt->r->cnt;
        mx = max(rt->r->mx, mx);
    }
    rt->cnt = cnt;
    rt->mx = mx;
}

pair<Node*, Node*> split(Node* rt, int k) {
    if (rt == nullptr) return {nullptr, nullptr};
    if (rt->x > k) {
        auto [rt1, rt2] = split(rt->l, k);
        rt->l = rt2;
        upd(rt);
        return {rt1, rt};
    } else {
        auto [rt1, rt2] = split(rt->r, k);
        rt->r = rt1;
        upd(rt);
        return {rt, rt2};
    }
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

Node* root = nullptr;

void add(int x) {
    auto [rt1, rt2] = split(root, x);
    root = merge(merge(rt1, new Node(x)), rt2);
}

void del(int x) {
    auto [rt1, rt2] = split(root, x - 1);
    auto [rt3, rt4] = split(rt2, x);
    root = merge(rt1, rt4);
}

void get(int k) {
    auto [rt1, rt2] = split_k(root, root->cnt - k + 1);
    cout << rt1->mx << endl;
    root = merge(rt1, rt2);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            add(x);
        } else if (t == -1) {
            int x;
            cin >> x;
            del(x);
        } else {
            int k;
            cin >> k;
            get(k);
        }
    }
    return 0;
}
