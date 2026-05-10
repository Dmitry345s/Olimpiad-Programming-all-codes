#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

int MAX = 2e5, h = 19;
vector<vector<int>> g(MAX);
vector<int> tin(MAX), fup(MAX), used2(MAX), ts(MAX);
int timer = 0;

void dfs(int v, int p = -1) {
    used2[v] = 1;
    tin[v] = fup[v] = timer++;
    int cnt = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (used2[to]) {
            fup[v] = min(fup[v], tin[to]);
        } else {
            cnt++;
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
        }
        if (tin[v] <= fup[to] && p != -1) {
            ts[v] = 1;
        }
    }
    if (p == -1 && cnt > 1) {
        ts[v] = 1;
    }
}

vector<int> used3(MAX, -1);
vector<vector<int>> g2(MAX), up(MAX, vector<int> (h));
vector<int> tout(MAX);
set<pair<int, int>> st;

void dfs2 (int v, int c) {
    used3[v] = c;
    for (int to : g[v]) {
        if (used3[to] == -1) {
            dfs2(to, c);
        }
    }
}

void dfs3(int v, int p = 0) {
    up[v][0] = p;
    tin[v] = timer++;
    for (int i = 1; i < h; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g2[v]) {
        if (to != p) {
            dfs3(to, v);
        }
    }
    tout[v] = timer++;
}

bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    for (int i = h - 1; i >= 0; --i) {
        if (!upper(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        --v[i];
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    int c = 0;
    for (int i = 0; i < n; ++i) {
        if (ts[i]) {
            used3[i] = c;
            c++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used3[i] == -1) {
            dfs2(i, c);
            c++;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (used3[i] == used3[to]) continue;
            st.insert({used3[i], used3[to]});
        }
    }
    set<pair<int, int>> :: iterator it;
    for (it = st.begin(); it != st.end(); ++it) {
        int a = (*it).first, b = (*it).second;
        g2[a].push_back(b);
    }
    timer = 0;
    dfs3(0);
    vector<int> used(n), d(n, 1e9);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (i == v[i]) {
            used[i] = 1;
            q.push(i);
            d[i] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (to == v[i]) {
                if (!used[i]) {
                    used[i] = 1;
                    q.push(i);
                    d[i] = 1;
                }
            }
            if (ts[to]) {
                int x = lca(used3[v[i]], used3[v[to]]);
                int z = used3[to];
                if ((upper(x, z) && upper(z, used3[v[i]])) || (upper(x, z) && upper(z, used3[v[to]]))) {
                    if (!used[i]) {
                        q.push(i);
                        used[i] = 1;
                        d[i] = 1;
                    }
                }
            }
        }
    }
    if (q.empty()) {
        for (int i = 0; i < n; ++i) {
            cout << "-1 " << endl;
        }
        cout << endl;
        return 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    cout << endl;
    return 0;
}
