#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

int solve(vector<vector<array<int, 3>>> & ln, vector<vector<array<int, 3>>> & st) {
    int ans = 0;
    for (int i = 0; i < (int)st.size(); ++i) {
        if ((int)st[i].size() == 0) {
            ans++;
            continue;
        }
        int now = 0, sid = 0;
        int x = st[i][0][0], y = i;
        if (st[i][0][1] == 1) {
            sid = 2;
        }
        int pref = 0;
        while (true) {
            if (now % 2 == 0) {
                int j = st[y][pref][2];
                if (sid == 0) {
                    j--;
                    if (j < 0) {
                        break;
                    }
                    y = ln[x][j][0];
                    if (ln[x][j][1] == 1) {
                        sid = 1;
                    } else {
                        sid = 3;
                    }
                    pref = j;
                } else {
                    j++;
                    if (j >= (int)ln[x].size()) break;
                    y = ln[x][j][0];
                    if (ln[x][j][1] == 1) {
                        sid = 3;
                    } else {
                        sid = 1;
                    }
                    pref = j;
                }
            } else {
                int j = ln[x][pref][2];
                if (sid == 1) {
                    j--;
                    if (j < 0) {
                        break;
                    }
                    x = st[y][j][0];
                    if (st[y][j][1] == 1) {
                        sid = 0;
                    } else {
                        sid = 2;
                    }
                    pref = j;
                } else {
                    j++;
                    if (j >= (int)st[y].size()) {
                        ans++;
                        break;
                    }
                    x = st[y][j][0];
                    if (st[y][j][1] == 1) {
                        sid = 2;
                    } else {
                        sid = 0;
                    }
                    pref = j;
                }
            }
            now += 1;
        }
        //cout << ans << " ";
    }
    //cout << endl;
    return ans;
}

signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> all(q);
    int ch = 0;
    for (int i = 0; i < q; ++i) {
        cin >> all[i][0] >> all[i][1] >> all[i][2];
        --all[i][1]; --all[i][2];
        ch = max(ch, all[i][0]);
    }
    int ans = 0;
    vector<vector<array<int, 3>>> ln(n);
    vector<vector<array<int, 3>>> st(m);
    for (int i = 0; i < q; ++i) {
        auto [t, x, y] = all[i];
        if (t == 0) {
            for (int i = 0; i < (int)ln[x].size(); ++i) {
                if (ln[x][i][0] == y) {
                    ln[x].erase(ln[x].begin() + i);
                    break;
                }
            }
            for (int i = 0; i < (int)ln[x].size(); ++i) {
                st[ln[x][i][0]][ln[x][i][2]][2] = i;
            }
            for (int i = 0; i < (int)st[y].size(); ++i) {
                if (st[y][i][0] == x) {
                    st[y].erase(st[y].begin() + i);
                    break;
                }
            }
            for (int i = 0; i < (int)st[y].size(); ++i) {
                ln[st[y][i][0]][st[y][i][2]][2] = i;
            }
        } else {
            int now = (int)ln[x].size();
            ln[x].push_back({y, t, -1});
            while (now > 0 && y < ln[x][now - 1][0]) {
                st[ln[x][now - 1][0]][ln[x][now - 1][2]][2]++;
                swap(ln[x][now], ln[x][now - 1]);
                now--;
            }
            int now2 = now;
            now = (int)st[y].size();
            st[y].push_back({x, t, -1});
            while (now > 0 && x < st[y][now - 1][0]) {
                ln[st[y][now - 1][0]][st[y][now - 1][2]][2]++;
                swap(st[y][now], st[y][now - 1]);
                now--;
            }
            ln[x][now2][2] = now;
            st[y][now][2] = now2;
        }
        //cout << f[x][y][0] << " " << f[x][y][1] << endl;
        int ch = solve(ln, st);
        cout << ch << endl;
    }
    return 0;
}
