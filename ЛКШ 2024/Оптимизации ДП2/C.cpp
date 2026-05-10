#include<bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

struct Line {
    long long k, b;
    Line(long long k = 0, long long b = -INF) : k(k), b(b) {};
    long long get(long long x) {
        return k * x + b;
    }
};

struct Node {
    Line a;
    int l_son, r_son;
    int l, r;
    Node(Line a = Line(), int l_son = -1, int r_son = -1, int l = -1, int r = -1) : a(a), l_son(l_son), r_son(r_son), l(l), r(r) {};
};

const int MAX = 5e6;
Node tree[MAX];
int timer = 0;

void update(Line new_line, int v) {
    //cout << v << " " << tree[v].l << " " << tree[v].r << endl;
    if (tree[v].l + 1 == tree[v].r) {
        if (tree[v].a.get(tree[v].l) < new_line.get(tree[v].l)) {
            swap(new_line, tree[v].a);
        }
        return;
    }
    int m = (tree[v].l + tree[v].r) / 2;
    //cout << new_line.k << " " << new_line.b << " " << tree[v].a.k << " " << tree[v].a.b << endl;
    //cout << new_line.get(m) << " " << tree[v].a.get(m) << endl;
    if (new_line.get(m) > tree[v].a.get(m)) {
        swap(new_line, tree[v].a);
    }
    //cout << new_line.k << " " << new_line.b << " " << tree[v].a.k << " " << tree[v].a.b << endl;
    if (tree[v].a.get(tree[v].l) < new_line.get(tree[v].l)) {
        if (tree[v].l_son == -1) {
            tree[timer] = Node(new_line, -1, -1, tree[v].l, m);
            tree[v].l_son = timer;
            timer++;
            return;
        }
        update(new_line, tree[v].l_son);
    } else {
        if (tree[v].r_son == -1) {
            tree[timer] = Node(new_line, -1, -1, m, tree[v].r);
            tree[v].r_son = timer;
            timer++;
            return;
        }
        update(new_line, tree[v].r_son);
    }
}

long long get(long long x, int v) {
    //cout << v << " " << tree[v].a.k << " " << tree[v].a.b << endl;
    if (tree[v].l + 1 == tree[v].r) {
        return tree[v].a.get(x);
    }
    int m = (tree[v].l + tree[v].r) / 2;
    if (x < m) {
        if (tree[v].l_son == -1) {
            return tree[v].a.get(x);
        }
        return max(tree[v].a.get(x), get(x, tree[v].l_son));
    } else {
        if (tree[v].r_son == -1) {
            return tree[v].a.get(x);
        }
        return max(tree[v].a.get(x), get(x, tree[v].r_son));
    }
}

signed main() {
    int n;
    cin >> n;
    vector<long long> x(n), c(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> c[i] >> t[i];
    }
    tree[0] = Node(Line(), -1, -1, -2e6, +2e6);
    timer++;
    vector<long long> dp(n);
    dp[0] = 0;
    update(Line(-c[0], c[0] * x[0] + dp[0]), 0);
    update(Line(c[0], -c[0] * x[0] + dp[0]), 0);
    for (int i = 1; i < n; ++i) {
        dp[i] = get(x[i], 0) + t[i];
        //cout << get(x[i], 0) << endl;
        //cout << dp[i] << endl;
        //cout << -c[i] << " " << c[i] * x[i] + dp[i] << endl;
        update(Line(-c[i], c[i] * x[i] + dp[i]), 0);
        update(Line(c[i], -c[i] * x[i] + dp[i]), 0);
    }
    cout << dp[n - 1] << endl;
    return 0;
}
