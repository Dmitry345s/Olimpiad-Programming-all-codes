#include<bits/stdc++.h>

#define int long long

using namespace std;
using ull = unsigned long long;

const int P = 179;

signed main() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = (int)s.size();
    int ans = n;
    for (int i = 1; i <= k; ++i) {
        ans = min(ans, n - (n / i) * (i - 1));
    }
    cout << ans << endl;
    return 0;
    /*vector<vector<pair<int, int>>> all(k + 1);
    for (int i = 0; i < n; ++i) {
        ull now = 0;
        for (int j = i; j < min(n, i + k); ++j) {
            now *= P;
            now += (s[j] - 'a' + 1);
            all[j - i + 1].push_back({now, i});
        }
    }
    int ans = n;
    vector<pair<int, int>> now;
    for (int i = 1; i <= k; ++i) {
        sort(all[i].begin(), all[i].end());
        int l = 1;
        now.push_back(all[i][0]);
        while (l < (int)all[i].size()) {
            if (all[i][l].first != now.back().first) {
                int cnt = 0;
                int ls = -k - 1;
                for (int j = 0; j < (int)now.size(); ++j) {
                    if (now[j].second >= ls + i) {
                        cnt++;
                        ls = now[j].second;
                    }
                }
                ans = min(ans, n - i * cnt + cnt);
                now.clear();
            }
            now.push_back(all[i][l]);
            l++;
        }
        int cnt = 0;
        int ls = -k - 1;
        for (int j = 0; j < (int)now.size(); ++j) {
            if (now[j].second >= ls + i) {
                cnt++;
                ls = now[j].second;
            }
        }
        ans = min(ans, n - i * cnt + cnt);
        now.clear();
    }
    cout << ans << endl;*/
    return 0;
}
