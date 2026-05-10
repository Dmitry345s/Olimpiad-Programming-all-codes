#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

vector<vector<int>> g(5 * 100000);
vector<bool> used(5 * 100000);
vector<pair<int, int>> dp(5 * 100000, {-1, -1});

void dfs(int v, int p = -1) {
    used[v] = true;
    if (g[v].size() == 1 && p != -1) {
        dp[v].second = 0;
        dp[v].first = 0;
    } else {
        int maxm = -1, maxm2 = -1;
        for (int to : g[v]) {
            if (!used[to]) {
                dfs(to, v);
                if (dp[to].second >= maxm) {
                    maxm2 = maxm;
                    maxm = dp[to].second;
                } else if (dp[to].second >= maxm2) {
                    maxm2 = dp[to].second;
                }
            }
        }
        dp[v].second = maxm + 1;
        if (maxm2 != -1) {
            dp[v].first = maxm + maxm2 + 2;
        } else {
            dp[v].first = dp[v].second;
        }
    }
}
int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    for (int l = 0; l < n - 1; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    dfs(0);
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i].first);
    }
    cout << ans + 1 << endl;
}
