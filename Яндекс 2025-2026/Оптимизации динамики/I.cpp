#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX = 1e5 + 1;
const ll INF = 1e11 + 1;

int a[MAX], b[MAX];

struct Line {
    ll k, b;
    Line(ll k = 0, ll b = INF) : k(k), b(b) {}
    ll get(int x) {
        return k * x + b;
    }
};

vector<Line> tree;
vector<pair<int, int>> sns;

void add(int v, int l, int r, Line now) {
    int m = (l + r) / 2;
    if (now.get(m) <= tree[v].get(m)) {
        swap(now, tree[v]);
    }
    if (l + 1 == r) return;
    if (now.get(l) <= tree[v].get(l)) {
        if (sns[v].first == -1) {
            sns[v].first = (int)tree.size();
            tree.push_back(Line());
            sns.push_back({-1, -1});
        }
        add(sns[v].first, l, m, now);
    } else {
        if (sns[v].second == -1) {
            sns[v].second = (int)tree.size();
            tree.push_back(Line());
            sns.push_back({-1, -1});
        }
        add(sns[v].second, m, r, now);
    }
}

ll get(int v, int l, int r, int x) {
    if (v == -1) return INF;
    ll u = tree[v].get(x);
    if (l + 1 == r) return u;
    int m = (l + r) / 2;
    if (x < m) return min(u, get(sns[v].first, l, m, x));
    return min(u, get(sns[v].second, m, r, x));
}

vector<int> all[MAX];
int rt[MAX];
ll dp[MAX];
vector<int> g[MAX];

void dfs(int v, int p) {
    int in = -1;
    int mx = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        if ((int)all[to].size() > mx) {
            in = to;
            mx = (int)all[to].size();
        }
    }
    if (in == -1) {
        all[v] = {v};
        dp[v] = 0;
        rt[v] = (int)tree.size();
        tree.push_back(Line(b[v], dp[v]));
        sns.push_back({-1, -1});
        return;
    }
    swap(all[v], all[in]);
    rt[v] = rt[in];
    for (int to : g[v]) {
        if (to == p || to == in) continue;
        for (int x : all[to]) {
            all[v].push_back(x);
            add(rt[v], -MAX, MAX, Line(b[x], dp[x]));
        }
    }
    all[v].push_back(v);
    dp[v] = get(rt[v], -MAX, MAX, a[v]);
    add(rt[v], -MAX, MAX, Line(b[v], dp[v]));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
        cout << dp[i] << " ";
    }
    cout << endl;
    return 0;
}
