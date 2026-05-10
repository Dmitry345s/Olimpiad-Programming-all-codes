#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

struct Line {
    int k, b;
    Line (int k = 0, int b = -INF) : k(k), b(b) {}
    int get(int x) {
        return k * x + b;
    }
};

struct Node {
    Line a;
    int l, r;
    Node(Line x = Line()) {
        a = x;
        l = -1;
        r = -1;
    }
};

const int C = 2e6 + 5;

vector<Node> tree(1);

void add(Line a, int v, int l, int r) {
    int m = (l + r) / 2;
    if (a.get(m) > tree[v].a.get(m)) {
        swap(tree[v].a, a);
    }
    if (l + 1 == r) return;
    if (a.get(l) > tree[v].a.get(l)) {
        if (tree[v].l == -1) {
            tree[v].l = (int)tree.size();
            tree.push_back(Node());
        }
        add(a, tree[v].l, l, m);
    } else {
        if (tree[v].r == -1) {
            tree[v].r = (int)tree.size();
            tree.push_back(Node());
        }
        add(a, tree[v].r, m, r);
    }
}

int get(int x, int v, int l, int r) {
    if (v == -1) return -INF;
    if (l + 1 == r) {
        return tree[v].a.get(x);
    }
    int now = tree[v].a.get(x);
    int m = (l + r) / 2;
    if (x < m) {
        return max(now, get(x, tree[v].l, l, m));
    }
    return max(now, get(x, tree[v].r, m, r));
}

signed main() {
    int n, c;
    cin >> n >> c;
    int ans = 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i != 0) {
            ans += (a[i] - c) * (a[i] - c);
        }
    }
    vector<int> dp(n);
    add(Line((c - a[0]), dp[0] - (c * c - a[0] * a[0])), 0, -C, C);
    for (int i = 1; i < n; ++i) {
        dp[i] = get(2 * a[i], 0, -C, C);
        add(Line((c - a[i]), dp[i] - (c * c - a[i] * a[i])), 0, -C, C);
    }
    cout << dp[n - 1] + ans << endl;
    return 0;
}
