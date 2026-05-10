#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e7 + 1;

int f[MAX];

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> s(m);
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        f[u]++;
    }
    for (int i = 0; i < m; ++i) {
        cin >> s[i].first;
        s[i].second = i;
    }
    sort(s.begin(), s.end());
    int bef = 0;
    int r = m - 1;
    vector<int> ans;
    for (int i = MAX - 1; i >= 0; --i) {
        int now = bef + f[i];
        //cout << now << endl;
        if (now >= k) {
            now -= k;
            bef = now;
        } else {
            bef = 0;
            int cnt = k - now;
            while (r >= 0 && cnt > 0 && s[r].first >= i) {
                ans.push_back(s[r].second);
                r--;
                cnt--;
            }
        }
    }
    if (bef != 0) {
        cout << -1 << endl;
        return 0;
    }
    cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
