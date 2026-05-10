/*#include<bits/stdc++.h>

using namespace std;

int a;
mt19937 rnd(228);

pair<int, int> get(int x, int y) {
    return {x + a / 2, y + a / 2};
}

vector<pair<int, int>> all;
vector<vector<int>> used;
vector<vector<int>> b;
vector<vector<int>> c;

int dfs(int x, int y, int col) {
    //cout << x << " " << y << endl;
    if (!(0 <= x && x < a && 0 <= y && y < a) || b[x][y] == -1) {
        return 1;
    }
    if (used[x][y] || b[x][y] == col) {
        return 0;
    }
    used[x][y] = 1;
    int res = 0;
    res |= dfs(x - 1, y, col);
    res |= dfs(x + 1, y, col);
    res |= dfs(x, y + 1, col);
    res |= dfs(x, y - 1, col);
    all.push_back({x, y});
    return res;
}

signed main() {
    int t, n, p, k;
    cin >> t >> n >> p >> k >> a;
    int num;
    cin >> num;
    b.assign(a, vector<int> (a, -1));
    c.assign(a, vector<int> (a, -1));
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            cin >> b[a / 2 - n + i][a / 2 - n + j];
        }
    }
    set<array<int, 3>> now_can;
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            if ((i + j) % 2 == 1) {
                if (b[i][j] == 0) {
                    now_can.insert({-i - j, i, j});
                    c[i][j] = 1;
                } else {
                    now_can.insert({i + j, i, j});
                    c[i][j] = 0;
                }
            }
        }
    }
    int bul = 0;
    int lastx = -1e9, lasty = -1e9;
    while(true) {
        int st1, st2, st3;
        cin >> st1 >> st2 >> st3;
        if (st1 == -3 && st2 == -3 && st3 == -3) return 0;
        if (st1 == -2 && st2 == -2 && st3 == -2) {
            auto [sum, x, y] = *now_can.begin();
            cout << x - a / 2 << " " << y - a / 2 << endl;
            b[x][y] = num;
            if (c[x][y]) {
                now_can.erase({-x - y, x, y});
                now_can.insert({x + y, x, y});
                c[x][y] = 0;
            }
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int x2 = x + i, y2 = y + j;
                    all.clear();
                    used.assign(a, vector<int> (a, 0));
                    if (!dfs(x2, y2, num)) {
                        for (auto [ch1, ch2] : all) {
                            if (b[ch1][ch2] != -1) {
                                b[ch1][ch2] = num;
                                if (c[ch1][ch2]) {
                                    now_can.erase({-ch1 - ch2, ch1, ch2});
                                    now_can.insert({ch1 + ch2, ch1, ch2});
                                    c[ch1][ch2] = 0;
                                }
                            }
                        }
                    }
                }
            }
            continue;
        }
        if (st1 == -1 && st2 == -1 && st3 == -1) {
            bul ^= 1;
            if (bul == 0) continue;
            n++;
            for (int i = 0; i < 2 * n + 1; ++i) {
                //cout << a / 2 - n << endl;
                b[a / 2 - n][a / 2 - n + i] = 0;
                b[a / 2 - n + i][a / 2 - n] = 0;
                if ((a / 2 - n + a / 2 - n + i) % 2 == 1) {
                    now_can.insert({-(a / 2 - n + a / 2 - n + i), a / 2 - n, a / 2 - n + i});
                    now_can.insert({-(a / 2 - n + a / 2 - n + i), a / 2 - n + i, a / 2 - n});
                    c[a / 2 - n][a / 2 - n + i] = 1;
                    c[a / 2 - n + i][a / 2 - n] = 1;
                }
            }
            for (int i = 0; i < 2 * n + 1; ++i) {
                //cout << a / 2 + n << endl;
                b[a / 2 + n][a / 2 + n - i] = 0;
                b[a / 2 + n - i][a / 2 + n] = 0;
                if ((a / 2 + n + a / 2 + n - i) % 2 == 1) {
                    now_can.insert({-(a / 2 + n + a / 2 + n - i), a / 2 + n, a / 2 + n - i});
                    now_can.insert({-(a / 2 + n + a / 2 + n - i), a / 2 + n - i, a / 2 + n});
                    c[a / 2 + n][a / 2 + n - i] = 1;
                    c[a / 2 + n - i][a / 2 + n] = 1;
                }
            }
            continue;
        }
        if (st1 == 0) {
            auto [x, y] = get(st2, st3);
            b[x][y] = -1;
            if (c[x][y]) {
                now_can.erase({-x - y, x, y});
                now_can.insert({x + y, x, y});
                c[x][y] = 0;
            }
            continue;
        }
        auto [x, y] = get(st2, st3);
        b[x][y] = st1;
        if (c[x][y]) {
            now_can.erase({-x - y, x, y});
            now_can.insert({x + y, x, y});
            c[x][y] = 0;
        }
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int x2 = x + i, y2 = y + j;
                all.clear();
                used.assign(a, vector<int> (a, 0));
                if (!dfs(x2, y2, st1)) {
                    for (auto [ch1, ch2] : all) {
                        if (b[ch1][ch2] != -1) {
                            b[ch1][ch2] = st1;
                            if (c[ch1][ch2]) {
                                now_can.erase({-ch1 - ch2, ch1, ch2});
                                now_can.insert({ch1 + ch2, ch1, ch2});
                                c[ch1][ch2] = 0;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < a; ++j) {
                //cout << b[i][j] << " ";
            }
            //cout << endl;
        }
    }
    return 0;
}*/
#include<bits/stdc++.h>

using namespace std;

int a, n;
mt19937 rnd(time(0));

pair<int, int> get(int x, int y) {
    return {x + a / 2, a / 2 - y};
}

vector<pair<int, int>> all;
vector<vector<int>> used;
vector<vector<int>> b;
vector<vector<int>> c;

int dfs(int x, int y, int col) {
    //cout << x << " " << y << endl;
    if (!(0 <= x && x < a && 0 <= y && y < a) || !(a / 2 - n <= x && x <= a / 2 + n && a / 2 - n <= y && y <= a / 2 + n)) {
        return 1;
    }
    if (used[x][y] || b[x][y] == col || b[x][y] == -1) {
        return 0;
    }
    used[x][y] = 1;
    int res = 0;
    res |= dfs(x - 1, y, col);
    res |= dfs(x + 1, y, col);
    res |= dfs(x, y + 1, col);
    res |= dfs(x, y - 1, col);
    all.push_back({x, y});
    return res;
}

pair<int, int> find_new() {
    for (int sum = (a / 2 + n) * 2; sum >= 0; sum -= 2) {
        for (int i = 0; i <= sum; ++i) {
            if (i < a && sum - i < a && b[i][sum - i] == 0) {
                return {i, sum - i};
            }
        }
    }
    for (int sum = (a / 2 + n) * 2 - 1; sum >= 0; sum -= 2) {
        for (int i = 0; i <= sum; ++i) {
            if (i < a && sum - i < a && b[i][sum - i] == 0) {
                return {i, sum - i};
            }
        }
    }
}

int c1 = 0, c2 = 0;

pair<int, int> find_new2() {
    vector<pair<int, int>> tr(4);
    tr[0] = {1, 0};
    tr[1] = {0, 1};
    tr[2] = {-1, 0};
    tr[3] = {0, -1};
    shuffle(tr.begin(), tr.end(), rnd);
    while (true) {
        if (b[c1][c2] == -1) {
            c1 = rnd() % (2 * n + 1) + a / 2 - n;
            c2 = rnd() % (2 * n + 1) + a / 2 - n;
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int now1 = c1 + tr[i].first, now2 = c2 + tr[i].second;
            if (0 <= now1 && now1 < a && 0 <= now2 && now2 < a) {
                if (b[now1][now2] == 0) {
                    return {now1, now2};
                }
            }
        }
        c1 = rnd() % (2 * n + 1) + a / 2 - n;
        c2 = rnd() % (2 * n + 1) + a / 2 - n;
        //cout << c1 << " " << c2 << endl;
    }
}

pair<int, int> find_new3() {
    int x = 0, y = 0;
    while(true) {
        if (b[x][y] == 0) return {x, y};
        x = rnd() % (2 * n + 1) + a / 2 - n;
        y = rnd() % (2 * n + 1) + a / 2 - n;
    }
}

pair<int, int> find_new4(int num, int x, int y) {
    int ch = rnd() % 4;
    if (ch <= 1) return find_new();
    if (ch == 2 && y > 0 && b[x][y - 1] == 0) return {x, y - 1};
    //if (ch == 3 && y < a - 1 && b[x][y + 1] == 0) return {x, y + 1};
    if (ch == 3 && x > 0 && b[x - 1][y] == 0) return {x - 1, y};
    //if (ch == 3 && x < a - 1 && b[x + 1][y] == 0) return {x + 1, y};
    return find_new();
}


pair<int, int> find_new5() {

}

signed main() {
    int t, p, k;
    cin >> t >> n >> p >> k >> a;
    int num;
    cin >> num;
    b.assign(a, vector<int> (a, -1));
    c.assign(a, vector<int> (a, -1));
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            cin >> b[a / 2 - n + i][a / 2 - n + j];
        }
    }
    int bul = 0;
    int lastx = -1e9, lasty = -1e9;
    pair<int, int> del = find_new();
    lastx = del.first;
    lasty = del.second;
    int ha = 0;
    while(true) {
        int st1, st2, st3;
        cin >> st1 >> st2 >> st3;
        if (st1 == -3 && st2 == -3 && st3 == -3) return 0;
        if (st1 == -2 && st2 == -2 && st3 == -2) {
            int x = lastx, y = lasty;
            b[x][y] = num;
            cout << y - a / 2 << " " << a / 2 - x << endl;
            used.assign(a, vector<int> (a, 0));
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int x2 = x + i, y2 = y + j;
                    all.clear();
                    if (!dfs(x2, y2, num)) {
                        for (auto [ch1, ch2] : all) {
                            if (b[ch1][ch2] != -1) {
                                b[ch1][ch2] = num;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < a; ++i) {
                for (int j = 0; j < a; ++j) {
                    //cout << b[i][j] << " ";
                }
                //cout << endl;
            }
            continue;
        }
        if (st1 == -1 && st2 == -1 && st3 == -1) {
            bul ^= 1;
            if (bul == 0) continue;
            n++;
            for (int i = 0; i < 2 * n + 1; ++i) {
                //cout << a / 2 - n << endl;
                b[a / 2 - n][a / 2 - n + i] = 0;
                b[a / 2 - n + i][a / 2 - n] = 0;
            }
            for (int i = 0; i < 2 * n + 1; ++i) {
                //cout << a / 2 + n << endl;
                b[a / 2 + n][a / 2 + n - i] = 0;
                b[a / 2 + n - i][a / 2 + n] = 0;
            }
            continue;
        }
        if (st1 == 0) {
            auto [y, x] = get(st2, st3);
            b[x][y] = -1;
            continue;
        }
        auto [y, x] = get(st2, st3);
        //cout << x << " " << y << endl;
        b[x][y] = st1;
        used.assign(a, vector<int> (a, 0));
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int x2 = x + i, y2 = y + j;
                all.clear();
                if (!dfs(x2, y2, st1)) {
                    if ((int)all.size() == 16) {
                        ha = 1;
                    }
                    for (auto [ch1, ch2] : all) {
                        if (b[ch1][ch2] != -1) {
                            b[ch1][ch2] = st1;
                        }
                    }
                }
            }
        }
        pair<int, int> del;
        if (!ha) {
            del = find_new4(num, x, y);
        } else {
            del = find_new4(num, x, y);
        }
        lastx = del.first;
        lasty = del.second;
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < a; ++j) {
                //cout << b[i][j] << " ";
            }
            //cout << endl;
        }
    }
    return 0;
}

