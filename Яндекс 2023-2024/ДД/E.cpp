#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct Node {
    long long x, y, cnt, sum;
    Node *l = nullptr, *r = nullptr;
    Node(int x1) {
        x = x1;
        y = rnd();
        cnt = 1;
        sum = x1;
    }
};

void upd(Node* rt) {
    long long cnt = 1, sum = rt->x;
    if (rt->l != nullptr) {
        cnt += rt->l->cnt;
        sum += rt->l->sum;
    }
    if (rt->r != nullptr) {
        cnt += rt->r->cnt;
        sum += rt->r->sum;
    }
    rt->cnt = cnt;
    rt->sum = sum;
}

pair<Node*, Node*> split_k(Node* rt, int k) {
    if (rt == nullptr) return {nullptr, nullptr};
    if (rt->cnt == k) return {rt, nullptr};
    if (k == 0) return {nullptr, rt};
    if (rt->l) {
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

pair<int, int> get1(int l, int r) {
    if (l % 2 == 0) {
        return {l / 2, r / 2};
    } else {
        return {(l + 1) / 2, r / 2};
    }
}

pair<int, int> get2(int l, int r) {
    if (l % 2 == 1) {
        return {(l + 1) / 2, (r + 1) / 2};
    } else {
        return {l / 2 + 1, (r + 1) / 2};
    }
}

Node* root1 = nullptr;
Node* root2 = nullptr;

signed main() {
    int ch = 0;
    while (true) {
        ch++;
        root1 = nullptr;
        root2 = new Node(0);
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) return 0;
        cout << "Swapper " << ch << ":" << endl;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (i & 1) {
                root2 = merge(root2, new Node(a[i]));
            } else {
                root1 = merge(root1, new Node(a[i]));
            }
        }
        //cout << root1->sum << " " << root2->sum << endl;
        for (int i = 0; i < m; ++i) {
            int t, l, r;
            cin >> t >> l >> r;
            --l; --r;
            auto [l1, r1] = get1(l, r);
            auto [l2, r2] = get2(l, r);
            //cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
            ++l1; ++r1; ++l2; ++r2;
            if (t == 1) {
                auto[rt1, rt2] = split_k(root2, r2);
                auto[rt3, rt4] = split_k(rt1, l2 - 1);
                auto[rt5, rt6] = split_k(root1, r1);
                auto[rt7, rt8] = split_k(rt5, l1 - 1);
                root2 = merge(merge(rt3, rt8), rt2);
                root1 = merge(merge(rt7, rt4), rt6);
                //cout << root1->sum << " " << root2->sum << endl;
            } else if (t == 2) {
                long long ans = 0;
                auto[rt1, rt2] = split_k(root2, r2);
                auto[rt3, rt4] = split_k(rt1, l2 - 1);
                if (rt4) {
                    ans += rt4->sum;
                }
                root2 = merge(merge(rt3, rt4), rt2);
                auto[rt5, rt6] = split_k(root1, r1);
                auto[rt7, rt8] = split_k(rt5, l1 - 1);
                if (rt8) {
                    ans += rt8->sum;
                }
                root1 = merge(merge(rt7, rt8), rt6);
                cout << ans << endl;
                //cout << root1->sum << " " << root2->sum << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
