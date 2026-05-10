#include<bits/stdc++.h>

using namespace std;

signed main() {
    /*int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n, vector<int> (n, -1));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = a[i];
    }
    for (int d = 2; d <= n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = (l + d - 1);
            if (r >= n) continue;
            for (int c = l; c < r; ++c) {
                if (dp[l][c] != -1 && dp[c + 1][r] != -1) {
                    int x = dp[l][c], y = dp[c + 1][r];
                    if (max(x, y) == min(x, y) + 1) {
                        dp[l][r] = max(x, y) + 1;
                        break;
                    }
                }
            }
        }
    }
    //cout << dp[1][4] << endl;
    const int INF = 1e9;
    vector<int> tans(n + 1, INF);
    vector<int> pr(n + 1, -1);
    tans[0] = 0;
    pr[0] = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j][i - 1] != -1 && tans[i] > tans[j] + 1) {
                tans[i] = tans[j] + 1;
                pr[i] = j;
            }
        }
        //cout << tans[i] << " ";
    }
    //cout << endl;
    vector<int> ans;
    int v = n;
    while (pr[v] != -1) {
        ans.push_back(dp[pr[v]][v - 1]);
        v = pr[v];
    }
    reverse(ans.begin(), ans.end());
    cout << (int)ans.size() << endl;
    for (int to : ans) cout << to << " ";
    cout << endl;*/
    vector<long long> a(100);
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i < 100; ++i) {
        a[i] = a[i - 1] + a[i - 2];
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
