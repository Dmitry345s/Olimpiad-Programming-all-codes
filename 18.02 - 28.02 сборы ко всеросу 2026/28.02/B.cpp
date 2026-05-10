#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 1;
array<int, 3> qs[MAX];
vector<pair<int, int>> tree[4 * MAX];
int cnt[4 * MAX];

void add(int v, int l, int r, int ql, int qr, pair<int, int> now) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree[v].push_back(now);
        return;
    }
    int m = (l + r) / 2;
    add(2 * v, l, m, ql, qr, now);
    add(2 * v + 1, m, r, ql, qr, now);
}

void add2(int v, int l, int r, int in) {
    cnt[v] += 1;
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    if (in < m) {
        add2(2 * v, l, m, in);
    } else {
        add2(2 * v + 1, m, r, in);
    }
}

int rt[5 * MAX];
int sz[5 * MAX];
int nr[5 * MAX][2];
vector<array<int, 4>> go_back;

int root(int v) {
    if (rt[v] == v) return v;
    return root(rt[v]);
}

void unite(int v, int u) {
    int rv = root(v);
    int ru = root(u);
    //cout << v << " " << u << endl;
    //cout << rv << " " << ru << endl;
    assert(v != u);
    if (sz[rv] > sz[ru]) {
        swap(rv, ru);
        swap(v, u);
    }
    rt[rv] = ru;
    sz[ru] += sz[rv];
    int fr;
    int wt;
    if (nr[ru][0] == u) {
        fr = 0;
        wt = nr[ru][0];
        if (nr[rv][0] == v) {
            nr[ru][0] = nr[rv][1];
        } else {
            nr[ru][0] = nr[rv][0];
        }
    } else {
        fr = 1;
        wt = nr[ru][1];
        if (nr[rv][0] == v) {
            nr[ru][1] = nr[rv][1];
        } else {
            nr[ru][1] = nr[rv][0];
        }
    }
    go_back.push_back({ru, rv, fr, wt});
}

void do_back() {
    auto val = go_back.back();
    go_back.pop_back();
    rt[val[1]] = val[1];
    sz[val[0]] -= sz[val[1]];
    nr[val[0]][val[2]] = val[3];
}

int ans[MAX][2];

void solve(int v, int l, int r) {
    if (cnt[v] == 0) return;
    for (auto [u1, u2] : tree[v]) {
        unite(u1, u2);
    }
    if (l + 1 == r) {
        int rv = root(qs[l][1]);
        ans[l][0] = nr[rv][0];
        ans[l][1] = nr[rv][1];
        for (int i = 0; i < (int)tree[v].size(); ++i) {
            do_back();
        }
        return;
    }
    int m = (l + r) / 2;
    solve(2 * v, l, m);
    solve(2 * v + 1, m, r);
    for (int i = 0; i < (int)tree[v].size(); ++i) {
        do_back();
    }
    //cout << v << " " << ncnt << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int R, C, q;
    cin >> R >> C >> q;
    vector<array<int, 3>> all;
    vector<vector<int>> rows(R);
    vector<vector<int>> cols(C);
    for (int i = 0; i < C; ++i) {
        all.push_back({1, 0, i});
        all.push_back({1, R, i});
        cols[i].push_back(0);
        cols[i].push_back(R);
    }
    for (int i = 0; i < R; ++i) {
        all.push_back({0, i, 0});
        all.push_back({0, i, C});
        rows[i].push_back(0);
        rows[i].push_back(C);
    }
    map<pair<int, int>, int> mp;
    map<pair<int, int>, int> tp;
    for (int i = 0; i < q; ++i) {
        char tp;
        cin >> tp;
        if (tp == '?') {
            int w, p;
            cin >> w >> p;
            qs[i] = {2, w, p};
        } else if (tp == '/') {
            int r, c;
            cin >> r >> c;
            qs[i] = {0, r, c};
            all.push_back({0, r, c});
            rows[r].push_back(c);
            all.push_back({0, r, c + 1});
            rows[r].push_back(c + 1);
            all.push_back({1, r, c});
            cols[c].push_back(r);
            all.push_back({1, r + 1, c});
            cols[c].push_back(r + 1);
            mp[{r, c}] = i;
        } else {
            int r, c;
            cin >> r >> c;
            qs[i] = {1, r, c};
            all.push_back({0, r, c});
            rows[r].push_back(c);
            all.push_back({0, r, c + 1});
            rows[r].push_back(c + 1);
            all.push_back({1, r, c});
            cols[c].push_back(r);
            all.push_back({1, r + 1, c});
            cols[c].push_back(r + 1);
            mp[{r, c}] = i;
        }
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for (int i = 0; i < R; ++i) {
        sort(rows[i].begin(), rows[i].end());
        rows[i].erase(unique(rows[i].begin(), rows[i].end()), rows[i].end());
        for (int j = 0; j < (int)rows[i].size() - 1; ++j) {
            int j2 = j + 1;
            array<int, 3> ver1 = array<int, 3>{0, i, rows[i][j]};
            array<int, 3> ver2 = array<int, 3>{0, i, rows[i][j2]};
            int rv1 = lower_bound(all.begin(), all.end(), ver1) - all.begin();
            int rv2 = lower_bound(all.begin(), all.end(), ver2) - all.begin();
            if (rows[i][j2] - rows[i][j] > 1 || mp.find({i, rows[i][j]}) == mp.end()) {
                add(1, 0, q, 0, q, {rv1, rv2});
            }
        }
    }
    for (int i = 0; i < C; ++i) {
        sort(cols[i].begin(), cols[i].end());
        cols[i].erase(unique(cols[i].begin(), cols[i].end()), cols[i].end());
        for (int j = 0; j < (int)cols[i].size() - 1; ++j) {
            int j2 = j + 1;
            array<int, 3> ver1 = array<int, 3>{1, cols[i][j], i};
            array<int, 3> ver2 = array<int, 3>{1, cols[i][j2], i};
            int rv1 = lower_bound(all.begin(), all.end(), ver1) - all.begin();
            int rv2 = lower_bound(all.begin(), all.end(), ver2) - all.begin();
            if (cols[i][j2] - cols[i][j] > 1 || mp.find({cols[i][j], i}) == mp.end()) {
                add(1, 0, q, 0, q, {rv1, rv2});
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (qs[i][0] == 2) continue;
        int v1 = lower_bound(all.begin(), all.end(), array<int, 3>{0, qs[i][1], qs[i][2]}) - all.begin();
        int v2 = lower_bound(all.begin(), all.end(), array<int, 3>{1, qs[i][1], qs[i][2]}) - all.begin();
        int v3 = lower_bound(all.begin(), all.end(), array<int, 3>{0, qs[i][1], qs[i][2] + 1}) - all.begin();
        int v4 = lower_bound(all.begin(), all.end(), array<int, 3>{1, qs[i][1] + 1, qs[i][2]}) - all.begin();
        add(1, 0, q, 0, i, {v1, v3});
        add(1, 0, q, 0, i, {v2, v4});
        if (qs[i][0] == 1) swap(v2, v4);
        add(1, 0, q, i, q, {v1, v2});
        add(1, 0, q, i, q, {v3, v4});
    }
    for (int i = 0; i < (int)all.size(); ++i) {
        rt[i] = i;
        sz[i] = 1;
        nr[i][0] = i;
        nr[i][1] = i;
    }
    for (int i = 0; i < q; ++i) {
        if (qs[i][0] == 2) {
            int v;
            int w = qs[i][1];
            if (w == 0) {
                v = lower_bound(all.begin(), all.end(), array<int, 3>{1, 0, qs[i][2]}) - all.begin();
            } else if (w == 2) {
                v = lower_bound(all.begin(), all.end(), array<int, 3>{1, R, qs[i][2]}) - all.begin();
            } else if (w == 1) {
                v = lower_bound(all.begin(), all.end(), array<int, 3>{0, qs[i][2], C}) - all.begin();
            } else {
                v = lower_bound(all.begin(), all.end(), array<int, 3>{0, qs[i][2], 0}) - all.begin();
            }
            qs[i][1] = v;
            add2(1, 0, q, i);
        }
    }
    solve(1, 0, q);
    for (int i = 0; i < q; ++i) {
        if (qs[i][0] == 2) {
            auto [v1, v2] = ans[i];
            if (v1 == qs[i][1]) {
                array<int, 3> now = all[v2];
                if (now[0] == 0) {
                    cout << 1 + 2 * (now[2] == 0) << " " << now[1] << endl;
                } else {
                    cout << 2 * (now[1] == R) << " " << now[2] << endl;
                }
            } else {
                array<int, 3> now = all[v1];
                if (now[0] == 0) {
                    cout << 1 + 2 * (now[2] == 0) << " " << now[1] << endl;
                } else {
                    cout << 2 * (now[1] == R) << " " << now[2] << endl;
                }
            }
        }
    }
    cout << endl;
    return 0;
}
