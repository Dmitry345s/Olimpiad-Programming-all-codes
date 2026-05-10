#include<bits/stdc++.h>

#define int long long

using namespace std;

bool ch(string a, string s) {
    if (a.size() < s.size()) {
        return 1;
    }
    for (int i = 0; i < a.size() - s.size() + 1; ++i) {
        bool flag = 0;
        for (int j = i; j < i + s.size(); ++j) {
            if (a[j] != s[j - i]) {
                flag = 1;
            }
        }
        //cout << flag << endl;
        if (!flag) return 0;
    }
    return 1;
}

signed main() {
    string s;
    int n;
    cin >> s >> n;
    string s2 = s;
    reverse(s2.begin(), s2.end());
    int k = s.size() - 1;
    vector<vector<int>> dp((n + 1) / 2 + 1, vector<int> (1 << k));
    if (s.size() > n) {
        cout << (1 << ((n + 1) / 2)) << endl;
        return 0;
    }
    for (int i = 0; i < (1 << k); ++i) {
        dp[min((long long)s.size() - 1, (n + 1) / 2)][i] = 1;
    }
    for (int i = min((long long)s.size() - 1, (n + 1) / 2); i < (n + 1) / 2; ++i) {
        for (int j = 0; j < (1 << k); ++j) {
            //cout << i << " " << j << " " << dp[i][j] << endl;
            string now = "";
            for (int l = 0; l < min(i, k); ++l) {
                if ((j >> l) & 1) {
                    now.push_back('B');
                } else {
                    now.push_back('A');
                }
            }
            reverse(now.begin(), now.end());
            for (int _ = 0; _ < 2; ++_) {
                if (_) {
                    now.push_back('B');
                } else {
                    now.push_back('A');
                }
                if (now != s && now != s2) {
                    int mask = 0;
                    for (int l = 1; l < now.size(); ++l) {
                        mask *= 2;
                        if (now[l] == 'B') {
                            mask += 1;
                        }
                    }
                    //cout << i << " " << now << " " << j << endl;
                    dp[i + 1][mask] += dp[i][j];
                }
                now.pop_back();
            }
        }
    }
    //cout << dp.back()[0] << " " << dp.back()[1] << endl;
    int ans = 0;
    for (int i = 0; i < (1 << k); ++i) {
        //cout << i << " " << dp.back()[i] << endl;
        string now;
        for (int l = 0; l < k; ++l) {
            if ((i >> l) & 1) {
                now.push_back('B');
            } else {
                now.push_back('A');
            }
        }
        reverse(now.begin(), now.end());
        string now2 = now;
        reverse(now2.begin(), now2.end());
        for (int j = n % 2; j < now2.size(); ++j) {
            now.push_back(now2[j]);
        }
        //cout << now << endl;
        if (ch(now, s)) {
            //cout << 1 << endl;
            ans += dp.back()[i];
        }
    }
    cout << ans << endl;
    return 0;
}
