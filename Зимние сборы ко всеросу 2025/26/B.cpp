#include<bits/stdc++.h>

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<pair<int, char>> all;
        for (int i = 0; i < n; ++i) {
            int st = i;
            while (i < n && s[i] == s[st]) {
                i++;
            }
            all.push_back({i - st, s[st]});
        }
        /*vector<vector<int>> dp(n + 1, vector<int> (2 * n + 1));
        vector<vector<int>> pr(n + 1, vector<int> (2 * n + 1, -1));
        dp[0][0 + n] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 2 * n + 1; ++j) {
                int j2 = j + 1;
                int j3 =
            }
        }*/
        string rans = "#";
        vector<int> rans2;
        for (int i = 0; i < (1 << n); ++i) {
            int now = 0;
            string ans = "";
            vector<int> ans2;
            int cnt = -1;
            int fl = 1;
            for (int j = 0; j < n; ++j) {
                if (now == 0) {
                    cnt++;
                    if (cnt >= (int)ans.size()) {
                        ans.push_back(s[j]);
                        //cout << s[j] << " ";
                    } else {
                        if (ans[cnt] != s[j]) {
                            fl = 0;
                        }
                    }
                } else {
                    if (cnt < 0) {
                        fl = 0;
                        break;
                    }
                    if (ans[cnt] == s[j]) {
                        fl = 0;
                    }
                    cnt--;
                }
                //cout << i << " " << j << " " << cnt << endl;
                if (((i >> j) & 1) && j != n - 1) {
                    if (now == 0) {
                        ans2.push_back(cnt + 1);
                    } else {
                        ans2.push_back(cnt + 1);
                    }
                }
                now ^= ((i >> j) & 1);
            }
            if (fl && cnt == -1) {
                rans = ans;
                rans2 = ans2;
                break;
            }
        }
        if (rans == "#") {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        cout << (int)rans.size() << endl;
        cout << rans << endl;
        cout << (int)rans2.size() << endl;
        for (int i = 0; i < (int)rans2.size(); ++i) {
            cout << rans2[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
