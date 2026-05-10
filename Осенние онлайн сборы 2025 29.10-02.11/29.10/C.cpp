#include<bits/stdc++.h>

using namespace std;

using ushi = unsigned short int;

const int MAX = 200, INF = 2 * MAX;
vector<ushi> prec[MAX * MAX];
vector<ushi> prec2[MAX * MAX];
int dp[MAX][MAX * MAX][2];
pair<array<ushi, 3>, short int> p[MAX][MAX * MAX][2];

void precalc() {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX * MAX; ++j) {
            for (int k = 0; k < 2; ++k) {
                dp[i][j][k] = INF;
                p[i][j][k] = {{MAX, MAX * MAX, 3}, -2};
            }
        }
    }
    queue<array<ushi, 3>> q;
    dp[1][1][0] = 1;
    dp[1][1][1] = 1;
    q.push({1, 1, 1});
    q.push({1, 1, 0});
    while (!q.empty()) {
        auto v = q.front();
        int val = dp[v[0]][v[1]][v[2]];
        q.pop();
        for (int j = -1; j <= 1; ++j) {
            if (j == 0) {
                int fr = 1;
                int cnt = v[1] + 1;
                if (fr >= MAX || cnt >= MAX * MAX) continue;
                if (dp[fr][cnt][0] > val + 1) {
                    dp[fr][cnt][0] = val + 1;
                    p[fr][cnt][0] = {v, j};
                    q.push({fr, cnt, 0});
                }
                if (dp[fr][cnt][1] > val + 1) {
                    dp[fr][cnt][1] = val + 1;
                    p[fr][cnt][1] = {v, j};
                    q.push({fr, cnt, 1});
                }
            } else if (j == -1) {
                int fr = 0;
                int cnt = v[1];
                int sc = 0;
                if (v[2] == 0) {
                    fr = v[0] + 1;
                    cnt += fr;
                } else {
                    fr = 2;
                    cnt += 2;
                }
                if (fr >= MAX || cnt >= MAX * MAX) continue;
                if (dp[fr][cnt][sc] > val + 1) {
                    dp[fr][cnt][sc] = val + 1;
                    p[fr][cnt][sc] = {v, j};
                    q.push({fr, cnt, sc});
                }
            } else {
                int fr = 0;
                int cnt = v[1];
                int sc = 1;
                if (v[2] == 1) {
                    fr = v[0] + 1;
                    cnt += fr;
                } else {
                    fr = 2;
                    cnt += 2;
                }
                if (fr >= MAX || cnt >= MAX * MAX) continue;
                if (dp[fr][cnt][sc] > val + 1) {
                    dp[fr][cnt][sc] = val + 1;
                    p[fr][cnt][sc] = {v, j};
                    q.push({fr, cnt, sc});
                }
            }
        }
    }
    int un = MAX * MAX;
    for (int ans = 1; ans < MAX * MAX; ++ans) {
        for (int j = 0; j < MAX; ++j) {
            if (!prec[ans].empty()) break;
            for (int k = 0; k < 2; ++k) {
                if (!prec[ans].empty()) break;
                //cout << ans << " " << j << " " << k << endl;
                if (dp[j][ans][k] <= 200) {
                    int nowans = ans;
                    int nowj = j;
                    int nowk = k;
                    //cout << nowans << " " << nowj << " " << k << endl;
                    vector<int> to_ans;
                    while (p[nowj][nowans][nowk].second != -2) {
                        //cout << nowans << " " << ans << endl;
                        auto [v, js] = p[nowj][nowans][nowk];
                        to_ans.push_back(js);
                        nowans = v[1];
                        nowj = v[0];
                        nowk = v[2];
                    }
                    reverse(to_ans.begin(), to_ans.end());
                    prec[ans].push_back(400);
                    for (int dif : to_ans) {
                        prec[ans].push_back(prec[ans].back() + dif);
                    }
                    prec2[ans - (int)prec[ans].size()] = prec[ans];
                }
            }
        }
        if (prec[ans].empty()) {
            un = min(un, ans);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    precalc();
    vector<int> all;
    for (int u = 0; u < MAX * MAX; ++u) {
        if (!prec2[u].empty()) {
            all.push_back(u);
        }
    }
    reverse(all.begin(), all.end());
    bitset<5 * MAX * MAX> bag;
    bitset<5 * MAX * MAX> tr;
    vector<int> ps(5 * MAX * MAX);
    bag[0] = 1;
    for (int i = 0; i < 5; ++i) {
        for (int v : all) {
            tr = bag;
            bag = (bag | (bag << v));
            tr ^= bag;
            for (int x = tr._Find_next(0); x < 5 * MAX * MAX; x = tr._Find_next(x)) {
                ps[x] = v;
            }
        }
    }
    int tt = MAX * MAX;
    for (int u = 0; u < MAX * MAX; ++u) {
        if (!bag[u]) {
            tt = min(u, tt);
        }
    }
    //cout << tt << endl;
    int _;
    cin >> _;
    while (_--) {
        int x;
        cin >> x;
        if (x <= 200) {
            cout << 1 << " " << x << endl;
            for (int i = 0; i < x; ++i) {
                cout << 1 << " ";
            }
            cout << endl;
        } else if (x <= 40000) {
            if (x > 1000) {
                int n = 200;
                int m = x / 200;
                int u = x % 200;
                vector<vector<int>> ans(n, vector<int> (m));
                if (u != 1) {
                    for (int j = 0; j < u - 1; ++j) {
                        ans[j][0] = 1;
                    }
                } else {
                    for (int j = 0; j < n; ++j) {
                        ans[j][0] = 1;
                    }
                    ans[0][1] = 1;
                    m -= 1;
                }
                cout << n << " " << m << endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        cout << ans[i][j] << " ";
                    }
                    cout << endl;
                }
            } else {
                int n = 50;
                int m = x / 50;
                int u = x % 50;
                vector<vector<int>> ans(n, vector<int> (m));
                if (u != 1) {
                    for (int j = 0; j < u - 1; ++j) {
                        ans[j][0] = 1;
                    }
                } else {
                    for (int j = 0; j < n; ++j) {
                        ans[j][0] = 1;
                    }
                    ans[0][1] = 1;
                    m -= 1;
                }
                cout << n << " " << m << endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        cout << ans[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        } else if (x <= 4020000) {
            int rn = 0;
            int ttans = 0;
            for (int n = 1; n <= 200; ++n) {
                for (int i = 0; i < MAX * MAX; ++i) {
                    int uu = (int)prec[i].size();
                    if (uu != 0 && i * n <= x && (x - i * n) % uu == 0 && (x - i * n) / uu < MAX * MAX && !prec2[(x - i * n) / uu].empty()) {
                        ttans = i;
                        rn = n;
                        break;
                    }
                }
            }
            int n = rn;
            int ttans2 = (x - ttans * n) / (int)prec[ttans].size();
            int in = (int)prec[ttans].size();
            cout << n << " " << in << endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < in; ++j) {
                    int v = prec[ttans][j];
                    int u = 0;
                    if (i >= (int)prec2[ttans2].size()) {
                        u = (int)prec2[ttans2].size() - 1;
                    } else {
                        u = i;
                    }
                    cout << v + prec2[ttans2][u] * 401 << " ";
                }
                cout << endl;
            }
        } else {
            int n = 200;
            int m = 200;
            vector<vector<int>> ans(200, vector<int> (200));
            x -= 200 * (200 * 201) / 2;
            vector<int> trans(200);
            int mx = 0;
            for (int u = 0; u < MAX * MAX; ++u) {
                if (!prec2[u].empty()) {
                    mx = u;
                }
            }
            for (int i = 0; i < m; ++i) {
                if (x >= 5 * mx) {
                    trans[i] = mx;
                } else {
                    trans[i] = ps[x];
                }
                x -= trans[i];
            }
            assert(x == 0);
            cout << n << " " << m << endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    //cout << trans[j] << endl;
                    int y = 0;
                    if ((int)prec2[trans[j]].size() > i) {
                        y = i;
                    } else {
                        y = (int)prec2[trans[j]].size() - 1;
                    }
                    cout << prec2[trans[j]][y] + 401 * j << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;
}
