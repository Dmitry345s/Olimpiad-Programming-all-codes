#include<bits/stdc++.h>

using namespace std;

int MAX = 100;
vector<vector<pair<int, int>>> g(MAX);
vector<int> tr;

bool dfs(int a, int b, int p) {
    if (a == b) {
        return 1;
    }
    for (auto [to, i] : g[a]) {
        if (to == p) continue;
        bool flag = dfs(to, b, a);
        if (flag) {
            tr.push_back(i);
            return 1;
        }
    }
    return 0;
}

vector<int> now(MAX);

void dfs2(int v, vector<vector<int>> & g2, int p, int num) {
    now[v] = max(now[v], num);
    for (int to : g2[v]) {
        if (to == p) continue;
        dfs2(to, g2, v, num + 1);
    }
}

signed main() {
    int n, m, t;
    cin >> n >> m >> t;
    vector<pair<int, int>> all;
    vector<int> cnt(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        cnt[a]++;
        cnt[b]++;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        all.push_back({a, b});
    }
    int cen = -1;
    for (int i = 0; i < n; ++i) {
        if (cnt[i] == n - 1) {
            cen = i;
            break;
        }
    }
    /*for (int i = 0; i < m; ++i) {
        for (int j = 0; j < (int)gos[i].size(); ++j) {
            cout << gos[i][j] << " ";
        }
        cout << endl;
    }*/
    vector<int> ans(n);
    int minm = 1e9;
    if (n <= 15 && m <=15) {
        vector<vector<int>> gos(m), gos2(m);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            tr.clear();
            dfs(a, b, a);
            gos[i] = tr;
            gos2[i] = tr;
            reverse(gos2[i].begin(), gos2[i].end());
        }
        for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
            vector<vector<pair<int, int>>> to_ch(m), to_ch2(m);
            int flagall = 1;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < (int)gos[i].size(); ++j) {
                    if ((mask >> gos[i][j]) & 1) {
                        to_ch[i].push_back({all[gos[i][j]].second, all[gos[i][j]].first});
                    } else {
                        to_ch[i].push_back(all[gos[i][j]]);
                    }
                    if ((mask >> gos2[i][j]) & 1) {
                        to_ch2[i].push_back({all[gos2[i][j]].second, all[gos2[i][j]].first});
                    } else {
                        to_ch2[i].push_back(all[gos2[i][j]]);
                    }
                }
                int flag = 1;
                int flag2 = 1;
                for (int j = 1; j < (int)gos[i].size(); ++j) {
                    if (to_ch[i][j - 1].second != to_ch[i][j].first) {
                        flag = 0;
                    }
                    if (to_ch2[i][j - 1].second != to_ch2[i][j].first) {
                        flag2 = 0;
                    }
                }
                if (flag == 0 && flag2 == 0) {
                    flagall = 0;
                }
            }
            if (flagall == 0) continue;
            vector<vector<int>> g2(n);
            for (int i = 0; i < n - 1; ++i) {
                if ((mask >> i) & 1) {
                    g2[all[i].second].push_back(all[i].first);
                } else {
                    g2[all[i].first].push_back(all[i].second);
                }
            }
            //cout << mask << endl;
            now.assign(n, 0);
            for (int i = 0; i < n; ++i) {
                dfs2(i, g2, i, 1);
            }
            int u = 0;
            for (int i = 0; i < n; ++i) {
                u = max(u, now[i]);
            }
            if (u < minm) {
                ans = now;
                minm = u;
            }
        }
    } else {
        vector<vector<int>> gos(m);
        vector<vector<int>> put(n);
        //cout << cen << endl;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            gos[i] = {a, cen, b};
            put[a].push_back(b);
            put[b].push_back(a);
        }
        vector<int> used(n);
        int flag = 1;
        for (int i = 0; i < n; ++i) {
            if (i == cen) continue;
            if (used[i] == 0) {
                used[i] = 1;
            }
            //cout << i << " " << used[i] << endl;
            for (int j = 0; j < (int)put[i].size(); ++j) {
                if (used[put[i][j]] != 0 && used[put[i][j]] != used[i] * -1 && put[i][j] != cen) {
                    flag = 0;
                } else {
                    used[put[i][j]] = used[i] * -1;
                }
            }
        }
        if (flag != 0) {
            minm = 2;
            for (int i = 0; i < n; ++i) {
                if (i == cen) continue;
                if (used[i] == 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 3;
                    minm = 3;

                }
            }
            ans[cen] = 2;
        }
    }
    if (minm == 1e9) {
        cout << -1 << endl;
        return 0;
    }
    cout << minm << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
