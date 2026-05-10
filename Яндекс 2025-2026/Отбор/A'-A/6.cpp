#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 50;
int n, m, k;
int a[MAX][MAX], b[MAX][MAX];
int f[MAX][MAX];

int ch(int i, int j) {
    if (a[i][j] == 0) {
        return 0;
    }
    if (j >= 2 && a[i][j - 2] == a[i][j - 1] && a[i][j - 1] == a[i][j]) return 1;
    if (j >= 1 && j + 1 < m && a[i][j - 1] == a[i][j] && a[i][j] == a[i][j + 1]) return 1;
    if (j + 2 < m && a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2]) return 1;
    if (i >= 2 && a[i - 2][j] == a[i - 1][j] && a[i - 1][j] == a[i][j]) return 1;
    if (i >= 1 && i + 1 < n && a[i - 1][j] == a[i][j] && a[i][j] == a[i + 1][j]) return 1;
    if (i + 2 < n && a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j]) return 1;
    return 0;
}

vector<pair<int, int>> now_cmp;
int used[MAX][MAX];

void find_one_cmp(int i, int j) {
    used[i][j] = 1;
    now_cmp.push_back({i, j});
    if (i + 1 < n && !used[i + 1][j] && f[i + 1][j] && a[i + 1][j] == a[i][j]) {
        find_one_cmp(i + 1, j);
    }
    if (i > 0 && !used[i - 1][j] && f[i - 1][j] && a[i - 1][j] == a[i][j]) {
        find_one_cmp(i - 1, j);
    }
    if (j + 1 < m && !used[i][j + 1] && f[i][j + 1] && a[i][j + 1] == a[i][j]) {
        find_one_cmp(i, j + 1);
    }
    if (j > 0 && !used[i][j - 1] && f[i][j - 1] && a[i][j - 1] == a[i][j]) {
        find_one_cmp(i, j - 1);
    }
}

void fall_down() {
    for (int j = 0; j < m; ++j) {
        for (int i = n - 1; i >= 0; --i) {
            int now = i;
            while (now < n - 1 && a[now + 1][j] == 0) {
                swap(a[now + 1][j], a[now][j]);
                swap(b[now + 1][j], b[now][j]);
                now++;
            }
        }
    }
}

vector<pair<int, int>> all;
queue<pair<int, int>> spq;
int used2[MAX][MAX];

void upd(int i, int j, int tp) {
    if (tp == 1) {
        for (int j0 = 0; j0 < m; ++j0) {
            all.push_back({i, j0});
            if (b[i][j0] != 0 && used2[i][j0] == 0) {
                used2[i][j0] = 1;
                spq.push({i, j0});
            }
        }
    } else if (tp == 2) {
        for (int i0 = 0; i0 < n; ++i0) {
            all.push_back({i0, j});
            if (b[i0][j] != 0 && used2[i0][j] == 0) {
                used2[i0][j] = 1;
                spq.push({i0, j});
            }
        }
    } else if (tp == 3) {
        for (int j0 = 0; j0 < m; ++j0) {
            all.push_back({i, j0});
            if (b[i][j0] != 0 && used2[i][j0] == 0) {
                used2[i][j0] = 1;
                spq.push({i, j0});
            }
        }
        for (int i0 = 0; i0 < n; ++i0) {
            all.push_back({i0, j});
            if (b[i0][j] != 0 && used2[i0][j] == 0) {
                used2[i0][j] = 1;
                spq.push({i0, j});
            }
        }
    } else if (tp == 4) {
        for (int i0 = max(0ll, i - 1); i0 <= min(i + 1, n - 1); ++i0) {
            for (int j0 = max(0ll, j - 1); j0 <= min(j + 1, m - 1); ++j0) {
                all.push_back({i0, j0});
                if (b[i0][j0] != 0 && used2[i0][j0] == 0) {
                    used2[i0][j0] = 1;
                    spq.push({i0, j0});
                }
            }
        }
    } else if (tp == 5) {
        for (int i0 = max(0ll, i - 2); i0 <= min(i + 2, n - 1); ++i0) {
            for (int j0 = max(0ll, j - 2); j0 <= min(j + 2, m - 1); ++j0) {
                all.push_back({i0, j0});
                if (b[i0][j0] != 0 && used2[i0][j0] == 0) {
                    used2[i0][j0] = 1;
                    spq.push({i0, j0});
                }
            }
        }
    } else if (tp == 6) {
        for (int i0 = 0; i0 < n; ++i0) {
            for (int j0 = 0; j0 < m; ++j0) {
                if (a[i0][j0] == a[i][j]) {
                    all.push_back({i0, j0});
                    if (b[i0][j0] != 0 && used2[i0][j0] == 0) {
                        used2[i0][j0] = 1;
                        spq.push({i0, j0});
                    }
                }
            }
        }
    }
}

pair<int, int> one_round() {
    all.clear();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f[i][j] = ch(i, j);
            used[i][j] = 0;
            used2[i][j] = 0;
        }
    }
    pair<int, int> ans = {0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!used[i][j] && f[i][j]) {
                now_cmp.clear();
                find_one_cmp(i, j);
                int x = (int)now_cmp.size();
                ans.second += 50 * (x - 3) * (x - 3);
                for (auto [i, j] : now_cmp) {
                    all.push_back({i, j});
                    if (b[i][j] != 0) {
                        used2[i][j] = 1;
                        spq.push({i, j});
                    }
                }
            }
        }
    }
    while (!spq.empty()) {
        auto [i, j] = spq.front();
        spq.pop();
        upd(i, j, b[i][j]);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for (auto [i, j] : all) {
        ans.first += a[i][j];
        a[i][j] = 0;
        b[i][j] = 0;
    }
    fall_down();
    return ans;
}

int get_comb(vector<int> now) {
    for (int i = 0; i < 5; ++i) {
        if (now[i] == -1) return 0;
    }
    sort(now.begin(), now.end());
    if (now[0] == now[1] && now[1] == now[2] && now[2] == now[3] && now[3] == now[4]) return 1000 + now[0] * 10;
    if (now[0] == now[1] && now[1] == now[2] && now[2] == now[3]) return 750 + now[0] * 5;
    if (now[1] == now[2] && now[2] == now[3] && now[3] == now[4]) return 750 + now[1] * 5;
    if (now[0] == now[1] && now[1] == now[2] && now[3] == now[4]) return 500 + now[0] * 3 + now[3];
    if (now[0] == now[1] && now[2] == now[3] && now[3] == now[4]) return 500 + now[2] * 3 + now[0];
    if (now[0] == now[1] && now[1] == now[2]) return 300 + now[0] * 3;
    if (now[1] == now[2] && now[2] == now[3]) return 300 + now[1] * 3;
    if (now[2] == now[3] && now[3] == now[4]) return 300 + now[2] * 3;
    if (now[0] == now[1] && now[2] == now[3]) return 200 + now[2] * 2 + now[0];
    if (now[0] == now[1] && now[3] == now[4]) return 200 + now[3] * 2 + now[0];
    if (now[1] == now[2] && now[3] == now[4]) return 200 + now[3] * 2 + now[1];
    if (now[0] == now[1]) return 100 + now[0] * 2;
    if (now[1] == now[2]) return 100 + now[1] * 2;
    if (now[2] == now[3]) return 100 + now[2] * 2;
    if (now[3] == now[4]) return 100 + now[3] * 2;
    return 50 + now[4];
}

int get(vector<pair<int, int>> now) {
    int mx = 0;
    for (int mask = 0; mask < (1 << 5); ++mask) {
        vector<int> to_ch;
        for (int bt = 0; bt < 5; ++bt) {
            if ((mask >> bt) & 1) {
                to_ch.push_back(now[bt].first);
            } else {
                to_ch.push_back(now[bt].second);
            }
        }
        mx = max(mx, get_comb(to_ch));
    }
    return mx;
}

signed main() {
    int q;
    cin >> n >> m >> k >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> b[i][j];
        }
    }
    vector<pair<int, int>> now;
    int fl1 = 1;
    int fl2 = 1;
    int ans = 0;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1; --y1; --x2; --y2;
        if (a[x1][y1] == 0 || a[x2][y2] == 0 || (x1 != x2 && y1 != y2)) {
            fl1 = 0;
            continue;
        }
        swap(a[x1][y1], a[x2][y2]);
        swap(b[x1][y1], b[x2][y2]);
        int u1 = ch(x1, y1), u2 = ch(x2, y2);
        if (!u1 && !u2) {
            fl1 = 0;
            swap(a[x1][y1], a[x2][y2]);
            swap(b[x1][y1], b[x2][y2]);
            continue;
        }
        if (u1 && u2) {
            now.push_back({a[x1][y1], a[x2][y2]});
        } else if (u1) {
            now.push_back({a[x1][y1], -1});
        } else {
            now.push_back({-1, a[x2][y2]});
        }
        int num = 0;
        while (true) {
            num++;
            auto [cnt1, cnt2] = one_round();
            //cout << cnt1 << " " << cnt2 << endl;
            ans += num * cnt1;
            ans += cnt2;
            if (cnt1 == 0) break;
        }
        --num;
        ans += 80 * (num - 1) * (num - 1);
        if ((int)now.size() == 5) {
            ans += get(now);
            now.clear();
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j]) {
                fl2 = 0;
            }
        }
    }
    ans += fl1 * 1000;
    ans += fl2 * 10000;
    cout << ans << endl;
    return 0;
}
/*
2 3 100 1
2 3 2
3 2 3
0 0 0
0 0 0
1 2 2 2
*/
