#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 1e5;
vector<vector<array<int, 3>>> g(MAX);
vector<int> dp1(MAX), dp2(MAX), dp3(MAX), dp4(MAX);
int ans = 0, ans2 = 0;

void dfs(int v, int p = -1) {
    for (auto [to, c, d] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        if (d) {
            ans += (dp4[v] + 1) * (dp3[to] + c * dp4[to]);
            ans += dp3[v] * dp4[to];
            ans2 += (dp4[v] + 1) * dp4[to];
            dp1[v] += dp3[to] + c * dp4[to];
            dp2[v] += dp4[to];
        } else {
            ans += (dp4[v] + 1) * (dp1[to] + c * dp2[to]);
            ans += dp3[v] * dp2[to];
            ans += (dp3[to] + c * dp4[to]) * dp2[v];
            ans += dp4[to] * dp1[v];
            ans -= dp2[v] * (dp1[to] + c * dp2[to]);
            ans -= dp1[v] * dp2[to];
            ans2 += dp2[v] * dp4[to];
            ans2 += (dp4[v] + 1) * dp2[to];
            ans2 -= dp2[v] * dp2[to];
            dp1[v] += dp1[to] + c * dp2[to];
            dp2[v] += dp2[to];
        }
        dp4[v] += dp4[to];
        dp3[v] += dp3[to] + c * dp4[to];
        //cout << dp1[v] << " " << dp2[v] << " " << dp3[v] << " " << dp4[v] << endl;
        //cout << v << " " << to << " " << ans << endl;
    }
    dp4[v] += 1;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b;
        g[a].push_back({b, c, d});
        g[b].push_back({a, c, d});
    }
    dfs(0);
    //cout << ans << " " << ans2 << endl;
    if (ans2 == 0) {
        cout << 0 << endl;
        return 0;
    }
    cout << setprecision(15) << (double)ans / (double)ans2 << endl;
    return 0;
}
