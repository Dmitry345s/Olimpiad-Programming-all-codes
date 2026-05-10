#include<bits/stdc++.h>

//#define int long long

using namespace std;
using ll = long long;

const int MAX = 1e5 + 1, MOD = 1e9 + 7;

int a[MAX];
vector<int> g[MAX];
vector<pair<int, int>> all[MAX];
vector<int> del[MAX];
int cnt[MAX];

void sieve() {
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; j += i) {
            del[j].push_back(i);
        }
    }
}

ll sz[MAX], used[MAX], sum[MAX];
ll ans = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    sum[v] = 1;
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to, v);
        sz[v] += sz[to];
        sum[v] += sum[to] + sz[to];
        sum[v] %= MOD;
    }
    ll now = sz[v];
    ans += 1;
    ans %= MOD;
    for (int to : g[v]) {
        if (to == p || to == v) continue;
        now -= sz[to];
        ans += (sz[v] - sz[to]) * sum[to];
        ans += now * sz[to];
        ans %= MOD;
    }
}

signed main() {
    sieve();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        int t = __gcd(a[u], a[v]);
        for (auto wh : del[t]) {
            all[wh].push_back({u, v});
        }
    }
    for (int i = 0; i < n; ++i) {
        int t = a[i];
        for (auto wh : del[t]) {
            all[wh].push_back({i, i});
        }
    }
    vector<ll> now_ans(MAX);
    for (int i = 1; i < MAX; ++i) {
        for (auto [u, v] : all[i]) {
            g[u].clear();
            g[v].clear();
            used[u] = 0;
            used[v] = 0;
        }
        for (auto [u, v] : all[i]) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
        ans = 0;
        for (auto [u, v] : all[i]) {
            if (!used[u]) {
                dfs(u, u);
                ans = (ans - sz[u] + MOD) % MOD;
            }
        }
        now_ans[i] = ans;
    }
    for (int i = MAX - 1; i >= 1; --i) {
        for (int y : del[i]) {
            if (y == i) continue;
            now_ans[y] -= now_ans[i];
        }
    }
    ll rans = 0;
    for (int i = 0; i < MAX; ++i) {
        rans += now_ans[i] * i;
        rans %= MOD;
    }
    cout << rans << endl;
    return 0;
}
