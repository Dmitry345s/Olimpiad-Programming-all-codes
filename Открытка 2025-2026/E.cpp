#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10, LN = 20;
vector<int> g[MAX];
int up[2 * MAX][LN];
int h[MAX];
int tin[MAX];
int timer = 0;
int rtin[MAX];
vector<int> ord;
int n;
int pr[2 * MAX];
int f[MAX];

void dfsst(int v, int p) {
    h[v] = h[p] + 1;
    tin[v] = timer++;
    rtin[tin[v]] = v;
    f[v] = (int)ord.size();
    ord.push_back(v);
    for (int to : g[v]) {
        if (to == p) continue;
        dfsst(to, v);
        ord.push_back(v);
    }
}

void build() {
    pr[1] = 0;
    for (int i = 2; i < 2 * MAX; ++i) {
        pr[i] = pr[i / 2] + 1;
    }
    for (int i = 0; i < (int)ord.size(); ++i) {
        up[i][0] = tin[ord[i]];
    }
    for (int i = 1; i < LN; ++i) {
        for (int j = 0; j < (int)ord.size(); ++j) {
            up[j][i] = min(up[j][i - 1], up[min((int)ord.size() - 1, j + (1 << (i - 1)))][i - 1]);
        }
    }
}

int lca(int a, int b) {
    int l = f[a];
    int r = f[b];
    if (l > r) swap(l, r);
    r++;
    int ln = pr[r - l];
    return rtin[min(up[l][ln], up[r - (1 << ln)][ln])];
}

int dist(int a, int b) {
    int x = lca(a, b);
    return h[a] + h[b] - 2 * h[x];
}

int a[MAX];
int k;
int ch[MAX][LN];
int ans = MAX;

void dfs(int v, int p) {
    for (int i = 0; i < k; ++i) {
        ch[v][i] = -1;
        if ((a[v] >> i) & 1) {
            ch[v][i] = v;
        }
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        for (int i = 0; i < k; ++i) {
            if (ch[to][i] == -1) continue;
            if (ch[v][i] == -1) {
                ch[v][i] = ch[to][i];
                continue;
            }
            if (h[ch[v][i]] >= h[ch[to][i]]) {
                ch[v][i] = ch[to][i];
            }
        }
    }
}

void dfss(int v, int p) {
    for (int i = 0; i < k; ++i) {
        if (ch[p][i] == -1) continue;
        if (ch[v][i] == -1) {
            ch[v][i] = ch[p][i];
            continue;
        }
        if (dist(ch[v][i], v) > dist(ch[p][i], v)) {
            ch[v][i] = ch[p][i];
        }
    }
    int now = 0;
    for (int i = 0; i < k; ++i) {
        if (ch[v][i] == -1) return;
    }
    for (int i = 0; i < k; ++i) {
        for (int j = i + 1; j < k; ++j) {
            now = max(now, dist(ch[v][i], ch[v][j]));
        }
    }
    ans = min(ans, now);
    for (int to : g[v]) {
        if (to == p) continue;
        dfss(to, v);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    h[0] = -1;
    dfsst(0, 0);
    build();
    dfs(0, 0);
    dfss(0, 0);
    if (ans == MAX) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
