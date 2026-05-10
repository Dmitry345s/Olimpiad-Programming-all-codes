#include<bits/stdc++.h>

using namespace std;

int MAX = 1e6;
vector<vector<int>> g(MAX);
vector<int> h(MAX), dp(MAX), dp2(MAX);
int ans = 0;

void dfs(int v, int p = -1) {
    multiset<pair<int, int>> mh;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        //cout << v << " " << to << " " << h[to] + 1 << endl;
        mh.insert({h[to] + 1, to});
        dp[v] = max(dp[v], dp2[to] + 2);
        dp2[v] = max(dp2[v], dp2[to] + 2);
    }
    auto it = mh.rbegin();
    if (mh.size() == 0) {
        return;
    }
    //cout << (*it).first << endl;
    if (mh.size() > 1) {
        auto it2 = it;
        it2++;
        dp[v] = max(dp[v], ((*it).first + (*it2).first) * 2);
        dp2[v] = max(dp2[v], ((*it).first + (*it2).first) * 2);
    }
    if (mh.size() > 2) {
        auto it2 = it, it3 = it;
        it2++;
        it3++;
        it3++;
        //cout << (*it).first << " " << (*it2).first << " " << (*it3).first << endl;
        dp[v] = max(dp[v], ((*it).first + (*it2).first + (*it3).first) * 2);
    }
    //cout << v << " " << dp[v] << endl;
    h[v] = (*it).first;
    for (int to : g[v]) {
        if (to == p) continue;
        mh.erase({h[to] + 1, to});
        if (mh.size() == 0) {
            mh.insert({h[to] + 1, to});
            continue;
        }
        auto it = mh.rbegin();
        dp[v] = max(dp[v], dp2[to] + 2 + (*it).first * 2);
        mh.insert({h[to] + 1, to});
    }
    ans = max(ans, dp[v]);
    //cout << v << " " << h[v] << endl;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    cout << ans << endl;
    return 0;
}
