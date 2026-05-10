#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    string s, t;
    while (cin >> t) {
        for (auto c : t) {
            s.push_back(c);
        }
    }
    array<vector<int>, 26> cnt;
    for (int i = 0; i < (int)s.size(); ++i) {
        cnt[s[i] - 'a'].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        int last = -1;
        for (int j = 0; j < (int)cnt[i].size(); ++j) {
            ans += j * ((int)cnt[i].size() - 1 - j);
            ans += (cnt[i][j] - last - 1) * j * ((int)cnt[i].size() - j);
            last = cnt[i][j];
        }
        //cout << i + 'a' << " " << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
