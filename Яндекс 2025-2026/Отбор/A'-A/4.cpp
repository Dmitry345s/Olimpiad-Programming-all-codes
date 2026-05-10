#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;
vector<int> g[MAX];
int sz[MAX];
int dp[MAX];

bool cmp(int a, int b) {
    if (sz[a] - 2 * dp[a] == sz[b] - 2 * dp[b]) return a < b;
    return sz[a] - 2 * dp[a] < sz[b] - 2 * dp[b];
}

void dfs(int v) {
    sz[v] = 1;
    dp[v] = 1;
    vector<int> c;
    int suma = 0, sumb1 = 0, sumb2 = 0;
    for (int to : g[v]) {
        dfs(to);
        sz[v] += sz[to];
        if (sz[to] % 2) {
            c.push_back(to);
        } else {
            if (dp[to] <= sz[to] - dp[to]) {
                suma += dp[to];
            } else {
                sumb1 += dp[to];
                sumb2 += sz[to] - dp[to];
            }
        }
    }
    dp[v] += suma;
    if ((int)c.size() % 2) {
        dp[v] += sumb2;
    } else {
        dp[v] += sumb1;
    }
    sort(c.rbegin(), c.rend(), cmp);
    for (int i = 0; i < (int)c.size(); ++i) {
        int to = c[i];
        if (i % 2) {
            dp[v] += sz[to] - dp[to];
        } else {
            dp[v] += dp[to];
        }
    }
    //cout << v << " " << dp[v] << endl;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[p].push_back(i);
    }
    dfs(0);
    cout << dp[0] << endl;
    return 0;
}
