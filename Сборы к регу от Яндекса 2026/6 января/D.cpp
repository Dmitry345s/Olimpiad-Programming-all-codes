#include<bits/stdc++.h>

using namespace std;

const int LN = 70;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> cn(n, vector<int> (LN, -1));
    for (int i = 0; i < n; ++i) {
        cn[i][a[i]] = i;
        for (int j = a[i] + 1; j < LN; ++j) {
            int t1 = j - 1;
            int t2 = j - 2;
            if (cn[i][t1] - 1 >= 0 && cn[cn[i][t1] - 1][t2] >= 0) {
                cn[i][j] = cn[cn[i][t1] - 1][t2];
            }
            swap(t1, t2);
            if (cn[i][t1] - 1 >= 0 && cn[cn[i][t1] - 1][t2] >= 0) {
                cn[i][j] = cn[cn[i][t1] - 1][t2];
            }
        }
    }
    vector<int> dp(n + 1, n + 1);
    vector<int> p(n + 1);
    p[0] = -1;
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < LN; ++j) {
            if (cn[i - 1][j] == -1) continue;
            int now = dp[cn[i - 1][j]] + 1;
            if (now < dp[i]) {
                dp[i] = now;
                p[i] = j;
            }
        }
    }
    int ls = n;
    vector<int> ans;
    while (ls > 0) {
        ans.push_back(p[ls]);
        ls = cn[ls - 1][p[ls]];
    }
    reverse(ans.begin(), ans.end());
    cout << (int)ans.size() << endl;
    for (int v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
