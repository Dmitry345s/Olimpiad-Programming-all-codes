    #include<bits/stdc++.h>

    #define int long long

    using namespace std;

    signed main() {
        int n, m, k;
        cin >> n >> m >> k;
        vector<pair<int, int>> b(n);
        for (int i = 0; i < n; ++i) {
            cin >> b[i].first >> b[i].second;
        }
        if (n <= 10 && m <= 1000) {
            int rans = 0;
            for (int i = 0; i < (1 << n); ++i) {
                vector<int> ch(2 * m);
                for (int bit = 0; bit < n; ++bit) {
                    if ((i >> bit) & 1) {
                        for (int k = b[bit].first; k <= b[bit].second; ++k) {
                            ch[k] = (ch[k] ^ 1);
                        }
                    }
                }
                int nans = 0;
                for (int j = 0; j < 2 * m; ++j) {
                    nans += ch[j];
                }
                rans = max(rans, nans);
            }
            cout << rans << endl;
            return 0;
        }
        if (k == 1) {
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                ans += b[i].second - b[i].first + 1;
            }
            cout << ans << endl;
            return 0;
        }
        if (k == 2) {
            vector<int> l(n), r(n);
            for (int i = 0; i < n; ++i) {
                l[i] = b[i].first;
                r[i] = b[i].second;
            }
            vector<pair<int, int>> b2;
            for (int i = 0; i < n; ++i) {
                b2.push_back({l[i], i + 1});
                b2.push_back({r[i], -i - 1});
            }
            sort(b2.begin(), b2.end());
            vector<int> dp(n + 1);
            int cnt = 0;
            vector<int> ch(2 * n);
            vector<int> ch2(n + 1);
            dp[0] = 0;
            int last = 0;
            for (int i = 0; i < 2 * n; ++i) {
                auto [crd, t] = b2[i];
                if (t < 0) {
                    int j = -(t + 1);
                    auto u = lower_bound(b2.begin(), b2.end(), pair<int, int>{l[j], 0}) - b2.begin();
                    if (b[u] == b[ch2[j]]) {
                        u = upper_bound(b2.begin(), b2.end(), pair<int, int>{l[j], 2 * n}) - b2.begin();
                    }
                    auto [crd2, t2] = b2[u];
                    cnt++;
                    if (t2 > 0) {
                        dp[cnt] = max(dp[cnt - 1], dp[ch[ch2[j]]] + r[j] - l[j] + 1);
                    } else {
                        dp[cnt] = max(dp[cnt - 1], dp[ch[ch2[j]]] + r[j] - l[j] + 1);
                        dp[cnt] = max(dp[cnt], dp[ch[u]] + r[j] - l[j] + 1 - 2 * (crd2 - l[j] + 1));
                    }
                    last = r[j];
                    ch[i] = cnt;
                } else {
                    int j = t - 1;
                    ch2[j] = i;
                    if (last < l[j]) {
                        ch[i] = cnt;
                    } else {
                        ch[i] = cnt - 1;
                    }
                }
            }
            cout << dp.back() << endl;
        }
    }
