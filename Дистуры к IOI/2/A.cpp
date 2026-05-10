#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        mx = max(mx, a[i]);
    }
    /*if (mx == 0) {
        cout << (n - k + m - 1) / m << endl;
        return 0;
    }*/
    if (k == n) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> lson;
    vector<vector<int>> dp(n + 1, vector<int> (k + 1, INF));
    for (int y = 0; y <= k; ++y) {
        for (int i = 0; i <= y; ++i) {
            dp[i][y] = 0;
        }
    }
    dp[1][0] = 1;
    vector<vector<int>> all(n);
    all[a[0]].push_back(0);
    for (int i = 2; i <= n; ++i) {
        int x = a[i - 1];
        all[x].push_back(i - 1);
        int non = -1;
        if ((int)all[x].size() > m) {
            non = all[x][(int)all[x].size() - m - 1];
        }
        //cout << "% " << i << ": " << non << endl;
        if ((int)lson.size() >= max(k, 1) && lson[0] >= non) {
            dp[i] = dp[i - 1];
            continue;
        }
        vector<int> nlson;
        int fl = 0;
        for (int j = 0; j < (int)lson.size(); ++j) {
            if (fl == 0 && lson[j] > non) {
                nlson.push_back(non);
                fl = 1;
            }
            nlson.push_back(lson[j]);
        }
        if (!fl) {
            nlson.push_back(non);
        }
        if ((int)nlson.size() > k + 1) {
            nlson.erase(nlson.begin());
        }
        swap(nlson, lson);
        /*cout << "& " << i << ": ";
        for (int u : lson) {
            cout << u << " ";
        }
        cout << endl;*/
        if (k > 20) {
            for (int j = 0; j <= k; ++j) {
                int l = max((int)lson.size() - 1 - j, 0), r = (int)lson.size() - 1;
                while (l + 3 < r) {
                    int c = (l + r) / 2;
                    int c2 = c + 1;
                    int nowcnt1 = (int)lson.size() - 1 - c;
                    int nowcnt2 = (int)lson.size() - 1 - c2;
                    if (dp[lson[c] + 1][j - nowcnt1] < dp[lson[c2] + 1][j - nowcnt2]) {
                        r = c2;
                    } else {
                        l = c;
                    }
                }
                for (int u = l; u <= r; ++u) {
                    int nowcnt = (int)lson.size() - 1 - u;
                    dp[i][j] = min(dp[i][j], dp[lson[u] + 1][j - nowcnt] + 1);
                }
            }
        } else {
            for (int j = (int)lson.size() - 1; j >= 0; --j) {
                int nowcnt = (int)lson.size() - 1 - j;
                int jj = lson[j] + 1;
                if (nowcnt > k) break;
                for (int u = 0; u <= k - nowcnt; ++u) {
                    dp[i][u + nowcnt] = min(dp[i][u + nowcnt], dp[jj][u] + 1);
                }
            }
        }
    }
    int ans = INF;
    for (int y = 0; y <= k; ++y) {
        ans = min(ans, dp[n][y]);
    }
    cout << ans << endl;
    return 0;
}
