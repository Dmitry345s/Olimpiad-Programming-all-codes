#include<bits/stdc++.h>

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

//# define int long long

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int tr(int a) {
    int ans = a;
    for (int i = 2; i <= min(25, a); ++i) {
        while (ans % i == 0 && ans / i % i == 0) {
            ans /= i;
        }
    }
    return ans;
}

struct Node {
    long long ans;
    vector<pair<int, int>> prefs;
    vector<pair<int, int>> sufs;
    Node() {
        ans = 0;
        prefs = {};
        sufs = {};
    }
    Node(int a) {
        a = tr(a);
        prefs.push_back({a, 1});
        sufs.push_back({a, 1});
        if (a != 1) {
            ans = 1;
        } else {
            ans = 0;
        }
    }
};

Node operator + (Node a, Node b) {
    if (b.prefs.empty()) return a;
    if (a.prefs.empty()) return b;
    Node ans = Node();
    ans.ans = a.ans + b.ans;
    int u = (int)b.prefs.size() - 1;
    vector<int> prefsms(u + 2);
    for (int i = 0; i < u + 1; ++i) {
        prefsms[i + 1] = prefsms[i] + b.prefs[i].second;
    }
    int ls = 1;
    for (auto [g1, cnt1] : a.sufs) {
        for (; u >= 0; --u) {
            auto [g2, cnt2] = b.prefs[u];
            if (gcd(g1, g2 / ls) != 1) {
                ans.ans += 1ll * cnt1 * prefsms[u + 1];
                break;
            }
            ls = g2;
        }
    }
    for (auto [g1, cnt1] : a.prefs) {
        ans.prefs.push_back({g1, cnt1});
    }
    for (auto [g1, cnt1] : b.prefs) {
        auto [g2, cnt2] = ans.prefs.back();
        int u = gcd(g1, g2);
        if (u == g2) {
            ans.prefs.back().second += cnt1;
        } else {
            ans.prefs.push_back({u, cnt1});
        }
    }
    for (auto [g1, cnt1] : b.sufs) {
        ans.sufs.push_back({g1, cnt1});
    }
    for (auto [g1, cnt1] : a.sufs) {
        auto [g2, cnt2] = ans.sufs.back();
        int u = gcd(g1, g2);
        if (u == g2) {
            ans.sufs.back().second += cnt1;
        } else {
            ans.sufs.push_back({u, cnt1});
        }
    }
    return ans;
}

const int MAX = 1e5 + 1;
int a[MAX];
Node tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = Node(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
    assert(tree[v].sufs.size() <= 10 && tree[v].prefs.size() <= 10);
}

void update(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree[v] = Node(x);
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x);
    } else {
        update(2 * v + 1, m, r, in, x);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
    assert(tree[v].sufs.size() <= 10 && tree[v].prefs.size() <= 10);
}

Node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return Node();
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int in, x;
            cin >> in >> x;
            --in;
            update(1, 0, n, in, x);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            Node u = get(1, 0, n, l, r);
            cout << u.ans << '\n';
        }
    }
    return 0;
}
