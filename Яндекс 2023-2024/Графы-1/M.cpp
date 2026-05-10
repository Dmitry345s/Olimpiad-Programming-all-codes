#include<bits/stdc++.h>

using namespace std;

int MAX = 5e5;
vector<vector<int>> g(MAX);
vector<long long> cost(MAX), dp1(MAX), dp2(MAX);

void dfs(int v, int p) {
    long long sum = 0, sum2 = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sum += dp2[to];
        sum2 += min(dp1[to], dp2[to]);
    }
    dp1[v] = sum;
    dp2[v] = sum2 + cost[v];
}

vector<int> ans;

void dfs2(int v, int chp, int p) {
    for (int to : g[v]) {
        if (to == p) continue;
        if (!chp) {
            ans.push_back(to);
            dfs2(to, 1, v);
        } else {
            if (dp1[to] <= dp2[to]) {
                dfs2(to, 0, v);
            } else {
                ans.push_back(to);
                dfs2(to, 1, v);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    if (n == 1) {
        cout << cost[0] << " " << 1 << endl << 1 << endl;
        return 0;
    }
    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
        //cout << dp1[i] << " " << dp2[i] << " " << dp3[i] << endl;
    }
    cout << min(dp1[0], dp2[0]) << " ";
    if (dp1[0] <= dp2[0]) {
        dfs2(0, 0, 0);
    } else {
        ans.push_back(0);
        dfs2(0, 1, 0);
    }
    cout << ans.size() << endl;
    for (int i= 0; i < ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
