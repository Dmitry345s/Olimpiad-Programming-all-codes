#include<bits/stdc++.h>

using namespace std;

const long long INF = 2e18;

struct Line {
    long long k, b;
    Line(long long k = 0, long long b = INF) : k(k), b(b) {};
    long long get(long long x) {
        return k * x + b;
    }
};

struct Node {
    Line a;
    int l_son, r_son, l, r;
    Node(Line a1 = Line(), int l_son1 = -1, int r_son1 = -1, int l1 = -1, int r1 = -1) {
        a = a1;
        l_son = l_son1;
        r_son = r_son1,
        l = l1;
        r = r1;
    }
};

const int MAX = 1e5 + 5, MAXM = 3e6 + 3;
vector<vector<pair<int, int>>> g(MAX);
vector<long long> h(MAX), dp(MAX), s(MAX), vs(MAX);
vector<vector<pair<int, Line>>> go_back;
vector<Node> tree(1);
int timer = 1;

void update(Line new_line, int v) {
    go_back.back().push_back({v, tree[v].a});
    if (tree[v].l + 1 == tree[v].r) {
        if (new_line.get(tree[v].l) > tree[v].a.get(tree[v].l)) {
            swap(new_line, tree[v].a);
        }
        return;
    }
    int m = (tree[v].l + tree[v].r) / 2;
    if (new_line.get(m) < tree[v].a.get(m)) {
        swap(new_line, tree[v].a);
    }
    if (new_line.get(tree[v].l) < tree[v].a.get(tree[v].l)) {
        if (tree[v].l_son == -1) {
            tree.push_back(Node(new_line, -1, -1, tree[v].l, m));
            go_back.back().push_back({(int)tree.size() - 1, Line()});
            tree[v].l_son = (int)tree.size() - 1;
            return;
        }
        update(new_line, tree[v].l_son);
    } else {
        if (tree[v].r_son == -1) {
            tree.push_back(Node(new_line, -1, -1, m, tree[v].r));
            go_back.back().push_back({(int)tree.size() - 1, Line()});
            tree[v].r_son = (int)tree.size() - 1;
            return;
        }
        update(new_line, tree[v].r_son);
    }
}

long long get(long long x, int v) {
    if (tree[v].l + 1 == tree[v].r) {
        return tree[v].a.get(x);
    }
    int m = (tree[v].l + tree[v].r) / 2;
    if (x < m) {
        if (tree[v].l_son == -1) {
            return tree[v].a.get(x);
        }
        return min(tree[v].a.get(x), get(x, tree[v].l_son));
    } else {
        if (tree[v].r_son == -1) {
            return tree[v].a.get(x);
        }
        return min(tree[v].a.get(x), get(x, tree[v].r_son));
    }
}

void dfs(int v, int p, int del) {
    h[v] = h[p] + del;
    if (v == 0) {
        dp[0] = 0;
    } else {
        dp[v] = get(vs[v], 0) + s[v] + h[v] * vs[v];
    }
    //cout << v << " " << dp[v] << endl;
    go_back.push_back({});
    go_back.back().reserve(32);
    update(Line(-h[v], dp[v]), 0);
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        dfs(to, v, c);
    }
    for (auto [whr, wht] : go_back.back()) {
        tree[whr].a = wht;
    }
    go_back.pop_back();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    go_back.reserve(n + 5);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        --a; --b;
        g[a].push_back({b, d});
        g[b].push_back({a, d});
    }
    for (int i = 1; i < n; ++i) {
        cin >> s[i] >> vs[i];
    }
    tree[0] = Node(Line(), -1, -1, -1, (long long)1e9 + 3);
    dfs(0, 0, 0);
    for (int i = 1; i < n; ++i) {
        cout << dp[i] << " ";
    }
    cout << endl;
    return 0;
}
