#include<bits/stdc++.h>

using namespace std;

const int MAX = 210;
vector<int> g[MAX];
int sz[MAX];
int used[MAX];
int fl;

void j_sz(int v, int p) {
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p || used[to]) continue;
        j_sz(to, v);
        sz[v] += sz[to];
    }
}

vector<int> nc;

void dfs(int v, int p, int nsz) {
    sz[v] = 1;
    int mx = 0;
    for (int to : g[v]) {
        if (to == p || used[to]) continue;
        dfs(to, v, nsz);
        sz[v] += sz[to];
        mx = max(mx, sz[to]);
    }
    mx = max(mx, nsz - sz[v]);
    if (mx <= nsz / 2) {
        nc.push_back(v);
    }
}

int ps[MAX];

void dfs2(int v, int p) {
    ps[v] = p;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
    }
}

vector<int> do_pt(int v, int v2) {
    dfs2(v, v);
    vector<int> now;
    while (v2 != v) {
        now.push_back(v2);
        v2 = ps[v2];
    }
    reverse(now.begin(), now.end());
    return now;
}

signed main() {
    int _;
    cin >> _;
    string ss;
    cin >> ss;
    if (ss == "Roma") {
        int q;
        cin >> q;
        while (q--) {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                g[i].clear();
                used[i] = 0;
            }
            for (int i = 0; i < n - 1; ++i) {
                int u, v;
                cin >> u >> v;
                g[u].push_back(v);
                g[v].push_back(u);
            }
            vector<vector<int>> all;
            int s;
            cin >> s;
            int tr = 0;
            while (n > (1 << tr)) {
                tr++;
            }
            tr--;
            tr = max(tr, 1);
            for (int i = 0; i < tr; ++i) {
                nc.clear();
                j_sz(s, s);
                dfs(s, s, sz[s]);
                all.push_back(nc);
                assert(nc.size() <= 2);
                for (int c : nc) {
                    used[c] = 1;
                }
            }
            vector<int> pt;
            pt.push_back(s);
            for (int i = tr - 1; i >= 0; --i) {
                vector<int> now = do_pt(pt.back(), all[i][0]);
                //assert((int)now.size() <= (n + (1 << (i + 1)) - 1) / (1 << (i + 1)));
                while ((int)now.size() < (n + (1 << (i + 1)) - 1) / (1 << (i + 1)) + 2) {
                    now.push_back(all[i][0]);
                }
                assert((int)now.size() == (n + (1 << (i + 1)) - 1) / (1 << (i + 1)) + 2);
                for (int v : now) {
                    pt.push_back(v);
                }
            }
            while ((int)pt.size() < 10 * n + 1) {
                pt.push_back(all[0][0]);
            }
            assert((int)pt.size() == 10 * n + 1);
            for (int v : pt) {
                cout << v << " ";
            }
            cout << endl;
        }
    } else {
        int q;
        cin >> q;
        while (q--) {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                g[i].clear();
                used[i] = 0;
            }
            for (int i = 0; i < n - 1; ++i) {
                int u, v;
                cin >> u >> v;
                g[u].push_back(v);
                g[v].push_back(u);
            }
            vector<vector<int>> all;
            int s;
            cin >> s;
            int tr = 0;
            while (n > (1 << tr)) {
                tr++;
            }
            tr--;
            tr = max(tr, 1);
            for (int i = 0; i < tr; ++i) {
                nc.clear();
                j_sz(s, s);
                dfs(s, s, sz[s]);
                all.push_back(nc);
                assert(nc.size() <= 2);
                for (int c : nc) {
                    used[c] = 1;
                }
            }
            vector<int> pt;
            pt.push_back(s);
            for (int i = tr - 1; i >= 0; --i) {
                vector<int> now = do_pt(pt.back(), all[i][0]);
                int cnt = 1;
                while ((int)now.size() < (n + (1 << (i + 1)) - 1) / (1 << (i + 1)) + 2) {
                    now.push_back(all[i][cnt % (int)all[i].size()]);
                    cnt++;
                }
                assert((int)now.size() == (n + (1 << (i + 1)) - 1) / (1 << (i + 1)) + 2);
                for (int v : now) {
                    pt.push_back(v);
                }
            }
            int cnt = 0;
            while ((int)pt.size() < 10 * n + 1) {
                pt.push_back(all[0][cnt % (int)all[0].size()]);
                cnt++;
            }
            assert((int)pt.size() == 10 * n + 1);
            for (int v : pt) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
