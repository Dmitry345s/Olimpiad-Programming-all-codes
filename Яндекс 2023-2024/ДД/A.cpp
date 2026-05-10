#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct Node {
    int x, y;
    long long sum;
    Node *l = nullptr, *r = nullptr;
    Node(int x1) {
        x = x1;
        y = rnd();
        sum = x1;
    }
};

void upd(Node* rt) {
    long long s = rt->x;
    if (rt->l != nullptr) {
        s += rt->l->sum;
    }
    if (rt->r != nullptr) {
        s += rt->r->sum;
    }
    rt->sum = s;
}

pair<Node*, Node*> split(Node* rt, int k) {
    if (rt == nullptr) return {nullptr, nullptr};
    if (k < rt->x) {
        pair<Node*, Node*> rans = split(rt->l, k);
        rt->l = rans.second;
        upd(rt);
        return {rans.first, rt};
    } else {
        pair<Node*, Node*> rans = split(rt->r, k);
        rt->r = rans.first;
        upd(rt);
        return {rt, rans.second};
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

bool find1(Node* rt, int k) {
    if (rt == nullptr) return false;
    if (rt->x == k) return true;
    if (rt->x > k) {
        return find1(rt->l, k);
    }
    return find1(rt->r, k);
}

Node* root = nullptr;

signed main() {
    int n;
    cin >> n;
    long long last = 0, mod = 1e9;
    for (int i = 0; i < n; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int x;
            cin >> x;
            x = (last + (long long) x) % mod;
            if (!find1(root, x)) {
                auto [rt1, rt2] = split(root, x);
                root = merge(merge(rt1, new Node(x)), rt2);
            }
            last = 0;
        } else {
            int l, r;
            cin >> l >> r;
            auto [rt1, rt2] = split(root, l - 1);
            auto [rt3, rt4] = split(rt2, r);
            //cout << root->x << " " << rt3->x << endl;
            if (rt3 != nullptr) {
                last = rt3->sum;
            } else {
                last = 0;
            }
            cout << last << endl;
            root = merge(merge(rt1, rt3), rt4);
        }
    }
    return 0;
}
