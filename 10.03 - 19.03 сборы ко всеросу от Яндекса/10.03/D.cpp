#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5;
vector<pair<int, int>> g[MAX];
int used[MAX];
int k;
int ans[MAX], sz[MAX];
vector<int> ord;
vector<int> ed;

void dfs(int v, int p) {
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        ed.push_back(c);
        ord.push_back(to);
        dfs(to, v);
    }
}

int dif[MAX];

signed main() {
    int n;
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }
    for (int i = 0; i < n; ++i) {
        if ((int)g[i].size() == 1) {
            ord.push_back(i);
            dfs(i, i);
            break;
        }
    }
    vector<int> pref(n);
    pref[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        pref[i + 1] = pref[i] + ed[i];
    }
    for (int i = 0; i < n; ++i) {
        dif[i]++;
        int x = pref[i] + k;
        int j = upper_bound(pref.begin(), pref.end(), x) - pref.begin();
        if (j == n) continue;
        --j;
        ans[ord[j]] += (n - j - 1) * dif[i];
        dif[j] += dif[i];
    }
    reverse(ord.begin(), ord.end());
    reverse(ed.begin(), ed.end());
    pref[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        pref[i + 1] = pref[i] + ed[i];
    }
    fill(dif, dif + n, 0);
    for (int i = 0; i < n; ++i) {
        dif[i]++;
        int x = pref[i] + k;
        int j = upper_bound(pref.begin(), pref.end(), x) - pref.begin();
        if (j == n) continue;
        --j;
        ans[ord[j]] += dif[i] * (n - j - 1);
        dif[j] += dif[i];
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
