#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5 + 5, MAX2 = 1e6 + 3;
vector<vector<int>> g(MAX);
vector<int> c(MAX);
vector<int> sieve(MAX2), dp(MAX2);

void start() {
    dp[1] = 0;
    for (int i = 2; i < MAX2; ++i) {
        if (sieve[i]) continue;
        for (int j = i; j < MAX2; j += i) {
            sieve[j] = i;
        }
    }
    for (int i = 2; i < MAX2; ++i) {
        dp[i] = dp[i / sieve[i]] + 1;
    }
}

vector<int> dpc(MAX);

void dfs(int v) {
    for (int to : g[v]) {
        dpc[to] = dpc[v] + dp[c[to]];
        dfs(to);
    }
}

signed main() {
    start();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int d;
        cin >> d;
        --d;
        g[d].push_back(i + 1);
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    dpc[0] = dp[c[0]];
    dfs(0);
    for (int i = 0; i < q; ++i) {
        int v, u;
        cin >> v >> u;
        --v; --u;
        int ch = dpc[u] - dpc[v] + dp[c[v]];
        if (ch % 2 == 0) {
            cout << 36 << endl;
        } else {
            cout << 9 << endl;
        }
    }
    return 0;
}
