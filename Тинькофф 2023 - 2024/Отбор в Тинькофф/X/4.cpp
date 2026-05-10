#include<bits/stdc++.h>
#pragma GCC optimize ("Ofast","O3")
#define int long long

using namespace std;

int MAX = 1e3;
vector<vector<int>> a(MAX, vector<int> (MAX, -1)), b(MAX, vector<int> (MAX));
vector<pair<int, int>> justpzdc;
vector<int> cnts(1e6 + 5);
int cnt = 0;

void dfs (int i, int j, int cl, int n, int m) {
    justpzdc.clear();
    justpzdc.push_back({i, j});
    while (justpzdc.size() != 0) {
        auto [i, j] = justpzdc.back();
        justpzdc.pop_back();
        if (b[i][j]) continue;
        b[i][j] = cl;
        cnt++;
        if (i > 0 && a[i][j] == a[i - 1][j] && !b[i - 1][j]) {
            justpzdc.push_back({i - 1, j});
        }
        if (j > 0 && a[i][j - 1] == a[i][j] && !b[i][j - 1]) {
            justpzdc.push_back({i, j - 1});
        }
        if (i + 1 < n && a[i + 1][j] == a[i][j] && !b[i + 1][j]) {
            justpzdc.push_back({i + 1, j});
        }
        if (j + 1 < m && a[i][j + 1] == a[i][j] && !b[i][j + 1]) {
            justpzdc.push_back({i, j + 1});
        }
    }
}

vector<vector<int>> g2(1e6 + 5);
vector<int> used2(1e6 + 5);
vector<int> justpzdc2;
int nowans = 0;

void dfs2(int v) {
    justpzdc2.clear();
    justpzdc2.push_back(v);
    while (justpzdc2.size() != 0) {
        int v = justpzdc2.back();
        justpzdc2.pop_back();
        if (used2[v]) continue;
        nowans += cnts[v];
        used2[v] = 1;
        for (int to : g2[v]) {
            if (!used2[to]) {
                justpzdc2.push_back(to);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("outputch.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    int nums = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            //cout << i << " " << j << endl;
            if (!b[i][j]) {
                ++nums;
                cnt = 0;
                dfs(i, j, nums, n, m);
                cnts[nums] = cnt;
                //cout << nums << endl;
                //cout << cnt << endl;
            }
        }
    }
    if (nums == 1) {
        cout << n * m << endl;
        cout << a[0][0] << " " << a[0][0] << endl;
        return 0;
    }
    vector<vector<pair<int, int>>>mp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i < n - 1) {
                if (b[i][j] != b[i + 1][j]) {
                    mp.push_back({{min(a[i][j], a[i + 1][j]), max(a[i][j], a[i + 1][j])}, {b[i][j], b[i + 1][j]}});
                }
            }
            if (j < m - 1) {
                if (b[i][j] != b[i][j + 1]) {
                    mp.push_back({{min(a[i][j], a[i][j + 1]), max(a[i][j], a[i][j + 1])}, {b[i][j], b[i][j + 1]}});
                }
            }
        }
    }
    a.clear();
    b.clear();
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    //cout << mp.size() << endl;
    int maxm = 0, ans1 = -1, ans2 = -1;
    int l = 0, r = 0;
    while (r < mp.size()) {
        if (mp[l][0] != mp[r][0]) {
            l = r;
        }
        while (r < mp.size() && mp[r][0] == mp[l][0]) {
            auto [v, to] = mp[r][1];
            //cout << v << " " << to << endl;
            g2[v].push_back(to);
            g2[to].push_back(v);
            used2[v] = 0;
            used2[to] = 0;
            ++r;
        }
        int getans = 0;
        for (int i = l; i < r; ++i) {
            auto [v, to] = mp[i][1];
            if (!used2[v]) {
                nowans = 0;
                dfs2(v);
                getans = max(getans, nowans);
            }
            g2[v].clear();
            g2[v].clear();
        }
        if (maxm < getans) {
            maxm = getans;
            ans1 = mp[l][0].first;
            ans2 = mp[l][0].second;
        }
    }
    cout << maxm << endl;
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
