#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, to, cap, fl;
    Edge(int v = 0, int to = 0, int cap = 0, int fl = 0) : v(v), to(to), cap(cap), fl(fl) {}
};

const int MAX = 50 * 50 * 2 + 5, INF = 1e9;
vector<Edge> ed;
vector<int> g[MAX];

void add_ed(int v, int u, int cap) {
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(v, u, cap, 0));
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(u, v, 0, 0));
}

void add_fl(int i, int fl) {
    ed[i].cap -= fl;
    ed[i].fl += fl;
    ed[i ^ 1].cap += fl;
}

int t;
vector<int> used(MAX);
int ans = 0;
int timer = 1;

int dfs(int v, int can_flow) {
    if (v == t) {
        ans += can_flow;
        return can_flow;
    }
    if (used[v] == timer || can_flow == 0) return 0;
    used[v] = timer;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].to, min(can_flow, ed[ind].cap));
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    int st = n * m * 2, f = st + 1;
    vector<vector<char>> fld(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> fld[i][j];
            if (fld[i][j] == 'H') {
                if ((i + j) % 2) {
                    add_ed(i * m + j, f, 1);
                } else {
                    add_ed(st, i * m + j, 1);
                }
                cnt += 1;
            }
            if (fld[i][j] == 'O') {
                if ((i + j) % 2) {
                    add_ed(i * m + j, f, 2);
                } else {
                    add_ed(st, i * m + j, 2);
                }
                cnt += 2;
            }
            if (fld[i][j] == 'N') {
                if ((i + j) % 2) {
                    add_ed(i * m + j, f, 3);
                } else {
                    add_ed(st, i * m + j, 3);
                }
                cnt += 3;
            }
            if (fld[i][j] == 'C') {
                if ((i + j) % 2) {
                    add_ed(i * m + j, f, 4);
                } else {
                    add_ed(st, i * m + j, 4);
                }
                cnt += 4;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (fld[i][j] == '.') continue;
            if (i > 0 && fld[i - 1][j] != '.') {
                add_ed(i * m + j, (i - 1) * m + j, 1);
                //cout << i * m + j << " " << (i - 1) * m + j << endl;
            }
            if (j > 0 && fld[i][j - 1] != '.') {
                add_ed(i * m + j, i * m + j - 1, 1);
                //cout << i * m + j << " " << i * m + j - 1 << endl;
            }
            if (i < n - 1 && fld[i + 1][j] != '.') {
                add_ed(i * m + j, (i + 1) * m + j, 1);
                //cout << i * m + j << " " << (i + 1) * m + j << endl;
            }
            if (j < m - 1 && fld[i][j + 1] != '.') {
                add_ed(i * m + j, i * m + j + 1, 1);
                //cout << i * m + j << " " << i * m + j + 1 << endl;
            }
        }
    }
    t = f;
    while (dfs(st, INF)) {
        //cout << ans << endl;
        timer++;
    }
    //cout << ans << " " << cnt << endl;
    if (2 * ans == cnt && cnt != 0) {
        cout << "Valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }
    return 0;
}
