#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 5e5 + 3, ln = 20;
vector<vector<int>> g(MAX);
vector<vector<vector<pair<int, int>>>> up(2, vector<vector<pair<int, int>>> (ln, vector<pair<int, int>> (MAX)));
vector<int> sz(MAX), cnt(MAX), tin(MAX), tout(MAX);
int timer = 0;
int all = 0;

void dfs(int v, int p = 0) {
    tin[v] = timer;
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        if (sz[to] % 2 == 1) {
            cnt[v] += 1;
        }
    }
    if (cnt[v] >= 2) {
        all++;
    }
    tout[v] = timer++;
}

void dfs2(int v, int p = 0) {
    if (v == 0) {
        up[0][0][v] = {0, 0};
        up[1][0][v] = {0, 0};
    } else {
        if (cnt[p] < 2) {
            up[0][0][v] = {p, 0};
        } else {
            up[0][0][v] = {p, 1};
        }
        if (sz[v] % 2 == 0) {
            if (cnt[p] + 1 < 2) {
                up[1][0][v] = {p, 0};
            } else {
                up[1][0][v] = {p, 1};
            }
        } else {
            if (cnt[p] - 1 < 2) {
                up[1][0][v] = {p, 0};
            } else {
                up[1][0][v] = {p, 1};
            }
        }
    }
    for (int i = 1; i < ln; ++i) {
        up[0][i][v].first = up[0][i - 1][up[0][i - 1][v].first].first;
        up[0][i][v].second = up[0][i - 1][v].second + up[0][i - 1][up[0][i - 1][v].second].second;
        up[1][i][v].first = up[1][i - 1][up[1][i - 1][v].first].first;
        up[1][i][v].second = up[1][i - 1][v].second + up[1][i - 1][up[1][i - 1][v].second].second;
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
    }
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[0][i][a].first, b)) {
            a = up[0][i][a].first;
        }
    }
    return up[0][0][a].first;
}

int mch = 0;

pair<int, int> gup(int a, int b, int x) {
    int mcnt = 0;
    int mcnt2 = 0;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[0][i][a].first, b)) {
            mcnt += up[x % 2][i][a].second;
            mcnt2 += up[0][i][a].second;
            a = up[0][i][a].first;
        }
    }
    mch = a;
    return {mcnt, mcnt2};
}

vector<vector<int>> g2(MAX);
int all2 = 0;
int flag = 1;

void dfs3(int v, int p = 0) {
    for (int to : g2[v]) {
        if (to == p) continue;

    }
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    dfs2(0);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        vector<pair<int, int>> fst;
        for (int i = 0; i < k; ++i) {
            int a;
            cin >> a;
            --a;
            g2[a].clear();
            fst.push_back({tin[a], a});
        }
        sort(fst.begin(), fst.end());
        vector<pair<int, int>> fst2 = fst;
        for (int i = 0; i < k - 1; ++i) {
            int x = lca(fst[i].second, fst[i + 1].second);
            g2[x].clear();
            fst2.push_back({tin[x], x});
        }
        sort(fst2.begin(), fst2.end());
        vector<int> now;
        for (int i = 0; i < fst2.size(); ++i) {
            while (now.size() > 0 && !ch(now.back(), fst2[i].second)) {
                now.pop_back();
            }
            if (now.size() > 0) {
                g2[now.back()].push_back(fst2[i].second);
            }
            now.push_back(fst2[i].second);
        }
        if (fst2[0].second != 0) {
            g2[0].push_back(fst2[0].second);
        }
        all2 = all;
        dfs3(0);
    }
    return 0;
}
