#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e3 + 1;
vector<int> g[MAX];
int h[MAX];
int h2[MAX];

void dfs(int v, int p) {
    h[v] = 0;
    h2[v] = h2[p] + 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        h[v] = max(h[v], h[to] + 1);
    }
}

int cnt;
int st;
int used[MAX];
vector<int> np;

int who_win(int v, int v2) {
    vector<int> d2((int)np.size());
    vector<int> d1((int)np.size());
    set<pair<int, int>> st1;
    set<pair<int, int>> st2;
    for (int i = 1; i < (int)np.size(); ++i) {
        int nv = np[i];
        int mx = 0;
        for (int to : g[nv]) {
            if (!used[to]) {
                mx = max(mx, h[to] + 1);
            }
        }
        d2[i] = h2[v2] - h2[nv] + mx;
        st2.insert({d2[i], i});
    }
    for (int i = 0; i < (int)np.size() - 1; ++i) {
        int nv = np[i];
        int mx = 0;
        for (int to : g[nv]) {
            if (!used[to]) {
                mx = max(mx, h[to] + 1);
            }
        }
        d1[i] = h2[nv] - h2[v] + mx;
        st1.insert({d1[i], i});
    }
    int u = 0;
    int u2 = (int)np.size() - 1;
    int fl = 1;
    while (u < u2) {
        if (fl) {
            if (d1[u] > (*st2.rbegin()).first) {
                fl = 1;
                break;
            } else {
                st1.erase({d1[u], u});
                u += 1;
                st2.erase({d2[u], u});
                fl ^= 1;
            }
        } else {
            if (d2[u2] >= (*st1.rbegin()).first) {
                fl = 0;
                break;
            } else {
                st2.erase({d2[u2], u2});
                u2 -= 1;
                st1.erase({d1[u2], u2});
                fl ^= 1;
            }
        }
    }
    return fl;
}

bool cmp(int a, int b) {
    if (h[a] == h[b]) return a < b;
    return h[a] > h[b];
}

void solve(int v, int p) {
    np.push_back(v);
    used[v] = 1;
    int ch = 1;
    if (v != st) ch = who_win(st, v);
    if (!ch) {
        cnt = -1;
        return;
    }
    cnt++;
    sort(g[v].begin(), g[v].end(), cmp);
    for (int to : g[v]) {
        if (to == p) continue;
        solve(to, v);
        if (cnt == -1) return;
    }
    used[v] = 0;
    np.pop_back();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        int fl = 0;
        for (int i = 0; i < n; ++i) {
            cnt = 0;
            st = i;
            h2[i] = -1;
            fill(used, used + n, 0);
            np.clear();
            dfs(i, i);
            solve(i, i);
            if (cnt == n) {
                fl = 1;
                break;
            }
        }
        if (fl) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
