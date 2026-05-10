#include<bits/stdc++.h>

using namespace std;

const int MAX = 101;
vector<int> g[MAX];
vector<int> to_ans;
int f;

int dfs(int v, int p) {
    if (v == f) {
        to_ans.push_back(f);
        return 1;
    }
    for (int to : g[v]) {
        if (to == p || to == v) continue;
        int x = dfs(to, v);
        if (x) {
            to_ans.push_back(v);
            return 1;
        }
    }
    return 0;
}

int bfs(int st) {
    vector<int> d(MAX, MAX + 1);
    d[st] = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int v = q.front();
        cout << v << " " << to << endl;
        q.pop();
        for (int to : g[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    int in = st;
    int mx = 0;
    for (int i = 0; i < MAX; ++i) {
        if (d[i] != MAX + 1 && d[i] > mx) {
            mx = d[i];
            in = i;
        }
    }
    cout << mx << endl;
    return in;
}

vector<int> gt_d(int v) {
    int u = bfs(v);
    int tt = bfs(u);
    cout << v << " " << u << " " << tt << endl;
    f = u;
    to_ans.clear();
    dfs(tt, tt);
    return to_ans;
}

int yy;

void relax(int v, int p, int cnt, vector<vector<int>> & ans, vector<int> & us) {
    if (v != yy) {
        ans[v][cnt] = ans[yy][cnt];
    }
    //cout << v << " " << yy << endl;
    for (int to : g[v]) {
        if (us[to] || to == p || to == v) continue;
        relax(to, v, cnt, ans, us);
    }
}

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<vector<int>> ans(n, {-1});
        vector<vector<int>> now(n);
        vector<int> us(n);
        for (int i = 0; i < n; ++i) {
            now[i] = {i};
        }
        int cnt = 0;
        int v = 0;
        while (true) {
            vector<int> m_now = gt_d(v);
            for (auto u : m_now) {
                cout << u << " ";
            }
            cout << endl;
            if ((int)m_now.size() == 1) break;
            int y = 0;
            for (int i = 0; i < (int)m_now.size(); ++i) {
                //cout << cnt << " " << (int)now[m_now[i]].size() << endl;
                for (auto v : now[m_now[i]]) {
                    ans[v][cnt] = y;
                    us[v] = 1;
                }
                y++;
            }
            /*for (int i = 0; i < n; ++i) {
                for (int j = 0; j < cnt + 1; ++j) {
                    cout << ans[i][j] << " ";
                }
                cout << endl;
            }*/
            for (int i = 0; i < (int)m_now.size(); ++i) {
                yy = m_now[i];
                relax(yy, yy, cnt, ans, us);
            }
            cnt++;
            for (int i = 0; i < n; ++i) {
                ans[i].push_back(-1);
            }
            v = m_now[0];
            cout << v << endl;
            vector<pair<int, int>> ned;
            now[v].clear();
            vector<int> tr(n);
            for (int i = 0; i < (int)m_now.size(); ++i) {
                for (int u : now[m_now[i]]) {
                    now[v].push_back(u);
                }
                for (int to : g[m_now[i]]) {
                    ned.push_back({m_now[i], to});
                    vector<int> red;
                    for (int jj = 0; jj < (int)g[to].size(); ++jj) {
                        if (g[to][jj] == m_now[i]) continue;
                        red.push_back(g[to][jj]);
                    }
                    g[to] = red;
                }
                tr[m_now[i]] = 1;
                g[m_now[i]].clear();
            }
            for (auto [to1, to2] : ned) {
                if (tr[to2] == 0) {
                    g[v].push_back(to2);
                }
            }
        }
        cout << cnt << endl;
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < cnt; ++k) {
                cout << ans[i][k] << " ";
            }
            cout << endl;
        }
    }
}
