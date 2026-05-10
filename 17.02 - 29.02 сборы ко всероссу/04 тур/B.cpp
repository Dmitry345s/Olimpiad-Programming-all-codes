#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> h(2 * MAX);
vector<vector<int>> tog(2, vector<int> (MAX));
vector<int> tin(MAX), tout(MAX);
int ln = 18;
vector<vector<int>> up(ln, vector<int> (MAX));
int timer = 0;
int ans = 0;

void dfs(int v, int p = -1) {
    int cnt = 0;
    h[v] = 0;
    tin[v] = timer++;
    if (p == -1) {
        up[0][v] = v;
    } else {
        up[0][v] = p;
    }
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        cnt++;
        dfs(to, v);
        h[v] += h[to];
    }
    if (cnt == 0) {
        h[v] = 1;
    }
    tout[v] = timer++;
    if (p == -1) return;
    if (h[v] % 2 == 0) {
        ans += 2;
    } else {
        ans += 1;
    }
    //cout << v << " " << ans << endl;
}

void dfs2(int v, int p = -1) {
    if (p != -1) {
        tog[0][v] = tog[0][p];
        tog[1][v] = tog[1][p];
        tog[h[v] % 2][v] += 1;
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
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

vector<vector<int>> g2(MAX);
vector<int> h2(MAX);

void dfs3(int v, int p = -1) {
    for (int to : g2[v]) {
        if (to == p) continue;
        dfs3(to, v);
        h2[v] += h2[to];
    }
    //cout << v << " " << ans << endl;
}

int ans2 = ans;

void dfs4(int v, int p = - 1) {
    for (int to : g2[v]) {
        if (to == p) continue;
        if (h2[to] % 2) {
            int del1 = tog[0][to] - tog[0][v];
            int del2 = tog[1][to] - tog[1][v];
            ans2 -= del1 * 2 + del2;
            ans2 += del2 * 2 + del1;
        }
        dfs4(to, v);
    }
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> cnt(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[a]++;
        cnt[b]++;
    }
    int r = -1;
    int ch = 0;
    for (int i = 0; i < n; ++i) {
        if (cnt[i] > 1) {
            r = i;
        } else {
            ch++;
        }
    }
    dfs(r);
    dfs2(r);
    for (int i = 0; i < q; ++i) {
        int d;
        cin >> d;
        vector<int> get(d);
        vector<pair<int, int>> tr = {{tin[r], r}};
        for (int j = 0; j < d; ++j) {
            cin >> get[j];
            --get[j];
            if (g[get[j]].size() > 1) {
                ch++;
            } else {
                h2[get[j]] -= 1;
            }
            g[get[j]].push_back(-1);
            h2[get[j]] += 1;
            tr.push_back({tin[get[j]], get[j]});
        }
        sort(tr.begin(), tr.end());
        for (int i = 0; i < d; ++i) {
            int x = lca(tr[i].second, tr[i + 1].second);
            tr.push_back({tin[x], x});
        }
        sort(tr.begin(), tr.end());
        tr.erase(unique(tr.begin(), tr.end()), tr.end());
        vector<int> stc;
        for (int j = 0; j < tr.size(); ++j) {
            //cout << "! " << tr[j].second << " " << tout[tr[j].second] << endl;
            while (stc.size() > 0 && tout[stc.back()] < tout[tr[j].second]) {
                stc.pop_back();
            }
            if (stc.size() != 0) {
                g2[stc.back()].push_back(tr[j].second);
                //cout << stc.back() << " " << tr[j].second << endl;
            }
            stc.push_back(tr[j].second);
        }
        dfs3(r);
        ans2 = ans;
        dfs4(r);
        if (ch % 2) {
            cout << -1 << endl;
        } else {
            cout << ans2 + d << endl;
        }
        for (int j = 0; j < tr.size(); ++j) {
            g2[tr[j].second].clear();
            h2[tr[j].second] = 0;
        }
        for (int j = 0; j < d; ++j) {
            if (g[get[j]].size() > 2) {
                ch--;
            }
            g[get[j]].pop_back();
        }
    }
    return 0;
}
