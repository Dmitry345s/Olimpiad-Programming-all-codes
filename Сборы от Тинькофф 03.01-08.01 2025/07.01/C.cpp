#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1;
vector<int> g[MAX];
int sz[MAX], tin[MAX], head[MAX], tout[MAX];
int timer = 0;

void dfs(int v) {
    sz[v] = 1;
    for (int to : g[v]) {
        dfs(to);
        sz[v] += sz[to];
    }
}

void dfs3(int v, int h) {
    int flag = 0;
    head[v] = h;
    tin[v] = timer++;
    for (int to : g[v]) {
        if (flag) {
            dfs3(to, to);
        } else {
            dfs3(to, h);
        }
    }
    tout[v] = timer;
}

pair<int, int> all[MAX];

bool cmp(int a, int b) {
    if (all[a].first == all[b].first) {
        return tin[a] > tin[b];
    }
    return all[a].first < all[b].first;
}

int tree[4 * MAX], update_tree[4 * MAX];

void push(int v, int l, int r) {
    int m = (l + r) / 2;
    int x = update_tree[v];
    update_tree[2 * v] += x;
    tree[2 * v] += x * (m - l);
    update_tree[2 * v + 1] += x;
    tree[2 * v + 1] += x * (r - m);
    update_tree[v] = 0;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        update_tree[v] += x;
        tree[v] += (r - l) * x;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    update(2 * v, l, m, ql, qr, x); update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) return 0;
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    push(v, l, r);
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

int dp[MAX];

void dfs2(int v) {
    int sc = 0;
    for (int to : g[v]) {
        dfs2(to);
        sc += dp[to];
    }
    dp[v] = max(dp[v], sc);
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[p].push_back(i);
    }
    dfs(0);
    dfs3(0, 0);
    for (int i = 0; i < m; ++i) {
        int v, d, w;
        cin >> v >> d >> w;
        --v;
        all[v] = {d, w};
    }
    vector<int> tp;
    for (int i = 0; i < n; ++i) {
        if (all[i] == pair<int, int>{0, 0}) {
            all[i] = {MAX + 2, 0};
        }
        tp.push_back(i);
        //cout << tin[i] << " " << sz[i] << endl;
    }
    sort(tp.begin(), tp.end(), cmp);
    for (int v : tp) {
        int x = 0;
        for (int to : g[v]) {
            x += get(1, 0, n, tin[to], tin[to] + sz[to]);
        }
        cout << x << " " << v << endl;
        update(1, 0, n, tin[v], tin[v] + 1, -x);
        x += all[v].second;
        dp[v] = x;
        update(1, 0, n, tin[v], tin[v] + 1, +x);
    }
    cout << dp[0] << endl;
    return 0;
}
