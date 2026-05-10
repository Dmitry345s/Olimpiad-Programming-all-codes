#include<bits/stdc++.h>

//#define int long long

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    vector<vector<vector<int>>> g(m, vector<vector<int>> (n));
    for (int i = 1; i < n; ++i) {
        cin >> p[i];
    }
    vector<vector<int>> pr(m, vector<int> (n - 1));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            cin >> pr[i][j];
            g[i][p[pr[i][j]]].push_back(j);

        }
        for (int j = 0; j < n; ++j) {
            sort(g[i][j].begin(), g[i][j].end());
        }
    }
    vector<int> cnt(n, 0);
    set<pair<int, int>> st;
    vector<int> ch(m, 0);
    int ans = 0;
    //cout << 0 << endl;
    for (int i = 0; i < n - 1; ++i) {
        int flag = 0;
        for (int j = 0; j < m; ++j) {
            st.erase({cnt[pr[j][i]], pr[j][i]});
            cnt[pr[j][i]]++;
            st.insert({cnt[pr[j][i]], pr[j][i]});
            int u = i;
            if ((int)(g[j][pr[j][i]].size()) > 0) {
                u = max(u, g[j][pr[j][i]].back());
            }
            ch[j] = max(u, ch[j]);
            if (ch[j] > i) {
                flag = 1;
            }
        }
        if ((*(st.begin())).first != m || flag) {
            continue;
        }
        ans++;
        for (int j = 0; j < m; ++j) {
            ch[j] = i + 1;
        }
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
