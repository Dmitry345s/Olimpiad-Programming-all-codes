#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e5 + 5;
vector<int> g[MAX];
int used[MAX];
vector<int> tin;

void dfs(int v) {
    tin.push_back(v);
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, s, x;
    cin >> n >> s >> x;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<vector<int>> all((int)b.size());
    for (int i = 0; i < n; ++i) {
        int as = s - a[i];
        int ax = x ^ a[i];
        if (ax == as) {
            ax = -1;
        }
        int v = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        if (all[v].empty()) {
            int tos = lower_bound(b.begin(), b.end(), as) - b.begin();
            if (tos < (int)b.size() && b[tos] == as) {
                g[v].push_back(tos);
            }
            int tox = lower_bound(b.begin(), b.end(), ax) - b.begin();
            if (tox < (int)b.size() && b[tox] == ax) {
                g[v].push_back(tox);
            }
        }
        all[v].push_back(i);
    }
    if (x == 0) {
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; ++i) {
            int as = s - a[i];
            int now = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            int ch = lower_bound(b.begin(), b.end(), as) - b.begin();
            int cnt1 = (int)all[now].size();
            int cnt2 = 0;
            if (ch < (int)b.size()) {
                cnt2 += (int)all[ch].size();
            }
            if (as == a[i]) {
                if (cnt1 % 2 == 1) {
                    cout << "No" << endl;
                    return 0;
                }
            } else {
                if (cnt1 % 2 != cnt2 % 2) {
                    cout << "No" << endl;
                    return 0;
                }
                if (cnt1 % 2) {
                    ans.push_back({all[now].back(), all[ch].back()});
                    all[now].pop_back();
                    all[ch].pop_back();
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            int now = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            while (!all[now].empty()) {
                int ls = all[now].back();
                all[now].pop_back();
                ans.push_back({ls, all[now].back()});
                all[now].pop_back();
            }
        }
        cout << "Yes" << endl;
        for (auto [u, v] : ans) {
            cout << u + 1 << " " << v + 1 << endl;
        }
        return 0;
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < (int)b.size(); ++i) {
        if ((int)g[i].size() == 1 && !used[i]) {
            tin.clear();
            dfs(i);
            for (int i = 0; i < (int)tin.size() - 1; ++i) {
                int v = tin[i];
                int to = tin[i + 1];
                if ((int)all[v].size() > (int)all[to].size()) {
                    cout << "No" << endl;
                    return 0;
                }
                while (!all[v].empty()) {
                    ans.push_back({all[v].back(), all[to].back()});
                    all[v].pop_back();
                    all[to].pop_back();
                }
            }
            int nv = tin.back();
            if ((int)all[nv].size() == 0) continue;
            if (b[nv] + b[nv] == s) {
                if ((int)all[nv].size() % 2) {
                    cout << "No" << endl;
                    return 0;
                }
                while (!all[nv].empty()) {
                    int v = all[nv].back();
                    all[nv].pop_back();
                    int to = all[nv].back();
                    all[nv].pop_back();
                    ans.push_back({v, to});
                }
            } else {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        if (!used[i]) {
            //assert(0);
            tin.clear();
            dfs(i);
            vector<int> now((int)tin.size());
            for (int i = 0; i < (int)tin.size(); ++i) {
                now[i] = (int)all[tin[i]].size();
            }
            int cnt = 0;
            int mn = 0;
            int mn2 = n + 1;
            for (int i = 0; i < (int)now.size(); ++i) {
                cnt *= -1;
                cnt += now[i];
                if (i % 2 == 1) {
                    mn = min(mn, cnt);
                } else {
                    mn2 = min(mn2, cnt);
                }
            }
            mn *= -1;
            if (cnt != 0) {
                cout << "No" << endl;
                return 0;
            }
            if (mn > now[0] || mn > now.back() || mn > mn2) {
                cout << "No" << endl;
                return 0;
            }
            for (int j = 0; j < mn; ++j) {
                ans.push_back({all[tin[0]].back(), all[tin.back()].back()});
                all[tin[0]].pop_back();
                all[tin.back()].pop_back();
            }
            for (int i = 0; i < (int)tin.size() - 1; ++i) {
                int v = tin[i];
                int to = tin[i + 1];
                while (!all[v].empty()) {
                    ans.push_back({all[v].back(), all[to].back()});
                    all[v].pop_back();
                    all[to].pop_back();
                }
            }
        }
    }
    cout << "Yes" << endl;
    for (auto [u, v] : ans) {
        cout << u + 1 << " " << v + 1 << endl;
    }
}
