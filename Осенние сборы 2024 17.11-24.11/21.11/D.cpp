#include<bits/stdc++.h>

#define int long long

using namespace std;
const int MAX = 3e5 + 1;
vector<int> dp(MAX);
vector<vector<int>> g(MAX);
vector<int> u(MAX);

void dfs(int v, int p) {
    int sum = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sum += dp[to];
    }
    if (sum + u[v] >= 0) {
        dp[v] = u[v] + sum;
    } else {
        dp[v] = 0;
    }
}

signed main() {
    int n, s;
    cin >> n >> s;
    vector<int> x(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> p[i];
        --p[i];
    }
    /*if (s == (int)1e18) {
        for (int i = 0; i < n; ++i) {
            p[i]++;
            g[p[i]].push_back(i + 1);
            u[i + 1] = x[i];
        }
        dfs(0, -1);
        cout << dp[0] << endl;
        return 0;
    }*/
    int l = 0;
    vector<vector<pair<int, int>>> all;
    while (l < n) {
        int st = l;
        l++;
        while (l < n && p[l] != -1) {
            l++;
        }
        int r = l;
        int minm = 0;
        int now = 0;
        all.push_back({});
        all.back().push_back({0, 0});
        for (int i = st; i < r; ++i) {
            now += x[i];
            minm = min(minm, now);
            all.back().push_back({minm, now});
        }
        sort(all.back().rbegin(), all.back().rend());
    }
    set<array<int, 4>> st;
    for (int i = 0; i < (int)all.size(); ++i) {
        st.insert({-all[i][0].first, all[i][0].second, i, 0});
    }
    int f = s;
    vector<int> cnt((int)all.size());
    while(!st.empty() && -(*st.begin())[0] + f >= 0) {
        auto [minm_, now, i, j] = *st.begin();
        st.erase(st.begin());
        if (now > cnt[i]) {
            f -= cnt[i];
            cnt[i] = now;
            f += cnt[i];
        }
        if (j < (int)all[i].size() - 1) {
            st.insert({-all[i][j + 1].first, all[i][j + 1].second, i, j + 1});
        }
    }
    cout << f - s << endl;
}
