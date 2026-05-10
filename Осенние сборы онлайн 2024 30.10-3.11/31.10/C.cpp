#include<bits/stdc++.h>

using namespace std;

bitset<1000> f[50][50];

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> prec(50);
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        all[i] = {x, y};
        prec[y].push_back(x);
        for (int x1 = 0; x1 < k; ++x1) {
            for (int y1 = 0; y1 < k; ++y1) {
                int xr = x - x1, yr = y - y1;
                if (xr >= 0 && yr >= 0) {
                    f[xr][yr][i] = 1;
                }
            }
        }
    }
    if (k == 1) {
        int last = 0;
        for (int i = 0; i < 50; ++i) {
            sort(prec[i].begin(), prec[i].end());
            if ((int)prec[i].size() != 0) {
                last = i;
            }
        }
        //cout << prec[0].back() << endl;
        vector<vector<int>> dp(50, vector<int> (50, 30000));
        //cout << endl;
        for (int i = 0; i < 50; ++i) {
            if ((int)prec[0].size() == 0) {
                dp[i][0] = i;
            } else {
                dp[i][0] = prec[0].back() + abs(i - prec[0].back());
            }
            //cout << dp[i][0] << " ";
        }
        //cout << endl;
        for (int j = 0; j < 50 - 1; ++j) {
            for (int i = 0; i < 50; ++i) {
                for (int l = 0; l < 50; ++l) {
                    if ((int)prec[j + 1].size() == 0) {
                        dp[l][j + 1] = min(dp[l][j + 1], dp[i][j] + 1 + abs(l - i));
                    } else {
                        int cnt = abs(prec[j + 1][0] - prec[j + 1].back()) + abs(prec[j + 1].back() - l) + abs(i - prec[j + 1][0]);
                        int cnt2 = abs(prec[j + 1][0] - prec[j + 1].back()) + abs(prec[j + 1].back() - i) + abs(l - prec[j + 1][0]);
                        dp[l][j + 1] = min(dp[l][j + 1], min(cnt, cnt2) + dp[i][j] + 1);
                    }
                }
            }
        }
        int ans = 3000;
        for (int j = 0; j < 50; ++j) {
            ans = min(dp[j][last], ans);
            //cout << j << " " << dp[j][last] << endl;
        }
        cout << ans << endl;
    } else {
        vector<vector<vector<vector<int>>>> dp((1 << n), vector<vector<vector<int>>> (k, vector<vector<int>> (k, vector<int> (n, 3000000))));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                for (int l = 0; l < k; ++l) {
                    int now1 = all[i].first - j, now2 = all[i].second - l;
                    if (now1 >= 0 && now2 >= 0) {
                        dp[(1 << i)][j][l][i] = now1 + now2;
                    }
                }
            }
        }
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int j = 0; j < k; ++j) {
                for (int )
            }
        }
    }
    return 0;
}
