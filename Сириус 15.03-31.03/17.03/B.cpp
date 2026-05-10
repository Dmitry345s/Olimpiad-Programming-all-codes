#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<pair<int, int>> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back({a[i], i});
    }
    /*set<pair<int, int>> st;
    vector<int> next(n, -1);
    int r = n - 1;
    while (r >= 0) {
        if (st.size() > 0 && (*st.begin()).first > b[r].first) {
            next[r] = (*st.begin()).second;
        }
        if (st.size() > 0) {
            if ((*st.begin()).first == b[r].first) {
                st.erase(st.begin());
            }
        }
        st.insert({b[r].first, r});
        r--;
    }*/
    sort(b.begin(), b.end());
    vector<vector<int>> all;
    int l = 0;
    int cnt = -1;
    while (l < n) {
        all.push_back({});
        cnt += 1;
        while (l < n - 1 && b[l].first == b[l + 1].first) {
            all[cnt].push_back(b[l].second);
            l++;
        }
        all[cnt].push_back(b[l].second);
        l++;
    }
    vector<int> next(n, -1);
    vector<array<int, 2>> used(n, {0, 0});
    vector<int> used3(n);
    int now = 0;
    for (int i = 0; i < cnt; ++i) {
        used[now][0] = 1;
        for (int j = 0; j < all[i].size(); ++j) {
            //cout << all[i][j] << " ";
            int k = upper_bound(all[i + 1].begin(), all[i + 1].end(), all[i][j]) - all[i + 1].begin();
            if (k != all[i + 1].size()) {
                next[now + j] = now + all[i].size() + k;
            }
            used3[now + j] = (int)all[i].size() - j;
        }
        //cout << endl;
        now += all[i].size();
        used[now - 1][1] = 1;
    }
    used[now][0] = 1;
    for (int j = 0; j < all[cnt].size(); ++j) {
        //cout << all[i][j] << " ";
        used3[now + j] = (int)all[cnt].size() - j;
    }
    vector<array<int, 4>> dp(n, {1, 1, 1, 1});
    vector<int> rldp(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        if (i + 1 < n && b[i + 1].second > b[i].second) {
            for (int j = 0; j < 4; ++j) {
                if (j & 1)  {
                    if (b[i].first == b[i + 1].first) {
                        dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
                    }
                    continue;
                }
                dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
            }
        }
        if (next[i] != -1 && b[i].second < b[next[i]].second) {
            int ch = 0;
            if (used[i][1] != 1) {
                ch += 1;
            }
            if (used[next[i]][0] != 1) {
                ch += 2;
            }
            //cout << i << " " << ch << " " << next[i] << " " << used3[next[i]] << endl;
            for (int j = 0; j < 4; ++j) {
                if (j & 1) continue;
                if (j > 1 && ch > 1) continue;
                if (ch > 1) {
                    dp[i][j ^ ch] = max(dp[i][j ^ ch], used3[next[i]] + 1);
                } else {
                    dp[i][j ^ ch] = max(dp[i][j ^ ch], dp[next[i]][j] + 1);
                }
            }
        }
        for (int j = 0; j < 4; ++j) {
            if ((j & 1)) continue;
            rldp[i] = max(rldp[i], dp[i][j]);
        }
        //cout << dp[i] << endl;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            //cout << i << " " << j << " " << dp[i][j] << endl;
            ans = max(dp[i][j], ans);
        }
    }
    cout << n - ans << endl;
    return 0;
}
