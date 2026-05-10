#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<int> cl(MAX, 1e9), tin(MAX);
vector<int> all;
vector<vector<pair<int, int>>> g(MAX);

void dfs(int v, int p) {
    tin[v] = (int)all.size();
    all.push_back(v);
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        cl[to] = c;
    }
    all.push_back(v);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(0, -1);
    //cout << 0 << endl;
    int k = 450, k2 = 350;
    vector<array<int, 3>> qs2;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int l = min(tin[a], tin[b]) + 1, r = max(tin[a], tin[b]) + 1;
        qs2.push_back({l, r, i});
    }
    //cout << 0 << endl;
    sort(qs2.begin(), qs2.end());
    vector<vector<array<int, 3>>> qs((2 * n + k - 1) / k);
    for (int i = 0; i < q; ++i) {
        qs[qs2[i][0] / k].push_back({qs2[i][1], qs2[i][0], qs2[i][2]});
    }
    //cout << 0 << endl;
    vector<int> ans(q);
    for (int i = 0; i < (int)qs.size(); ++i) {
        if ((int)qs[i].size() == 0) continue;
        sort(qs[i].begin(), qs[i].end());
        int l = qs[i][0][1], r = qs[i][0][1];
        vector<int> cnt(n + 1);
        vector<int> cnt3((n + 1 + k2 - 1) / k2);
        for (int i = 0; i <= n; ++i) {
            cnt3[i / k2]++;
        }
        vector<int> cnt2(n);
        for (int j = 0; j < (int)qs[i].size(); ++j) {
            auto [nr, nl, x] = qs[i][j];
            if (nr == nl) {
                //ans[x] = 0;
                //continue;
            }
            while (r < nr) {
                cnt2[all[r]]++;
                int c = cl[all[r]];
                if (c > n) {
                    r++;
                    continue;
                }
                if (cnt2[all[r]] % 2) {
                    cnt[c]++;
                    if (cnt[c] == 1) {
                        cnt3[c / k2] -= 1;
                    }
                } else {
                    cnt[c]--;
                    if (cnt[c] == 0) {
                        cnt3[c / k2] += 1;
                    }
                }
                r++;
            }
            while (l < nl) {
                cnt2[all[l]]--;
                int c = cl[all[l]];
                if (c > n) {
                    l++;
                    continue;
                }
                if (cnt2[all[l]] % 2) {
                    cnt[c]++;
                    if (cnt[c] == 1) {
                        cnt3[c / k2] -= 1;
                    }
                } else {
                    cnt[c]--;
                    if (cnt[c] == 0) {
                        cnt3[c / k2] += 1;
                    }
                }
                l++;
            }
            while (l > nl) {
                l--;
                cnt2[all[l]]++;
                int c = cl[all[l]];
                if (c > n) {
                    continue;
                }
                if (cnt2[all[l]] % 2) {
                    cnt[c]++;
                    if (cnt[c] == 1) {
                        cnt3[c / k2] -= 1;
                    }
                } else {
                    cnt[c]--;
                    if (cnt[c] == 0) {
                        cnt3[c / k2] += 1;
                    }
                }
            }
            for (int z = 0; z < (int)cnt3.size(); ++z) {
                if (cnt3[z] != 0) {
                    for (int z2 = z * k2; z2 < min(n + 1, (z + 1) * k2); ++z2) {
                        if (cnt[z2] == 0) {
                            ans[x] = z2;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
