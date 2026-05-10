#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5, LN = 18;
vector<int> g[MAX];
int mn[MAX];
int up[MAX][LN];
int h[MAX];

void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    h[v] = h[p] + 1;
    mn[v] = v;
    for (int to : g[v]) {
        dfs(to, v);
        mn[v] = min(mn[v], mn[to]);
    }
}

bool cmp(int a, int b) {
    return mn[a] < mn[b];
}

int ord[MAX];
int timer = 0;

void dfs2(int v) {
    for (int to : g[v]) {
        dfs2(to);
    }
    ord[v] = timer;
    timer++;
}

int now[MAX];
set<pair<int, int>> all;

int get(int x) {
    for (int i = LN - 1; i >= 0; --i) {
        if (now[up[x][i]]) {
            x = up[x][i];
        }
    }
    return x;
}

void del(int v) {
    all.insert({ord[v], v});
    now[v] = 0;
}

int add() {
    int v = all.begin()->second;
    all.erase(all.begin());
    now[v] = 1;
    return v;
}

signed main() {
    int n, q;
    cin >> n >> q;
    int rt = -1;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        if (p != 0) {
            g[p - 1].push_back(i);
        } else {
            rt = i;
        }
    }
    dfs(rt, rt);
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end(), cmp);
    }
    dfs2(rt);
    for (int i = 0; i < n; ++i) {
        all.insert({ord[i], i});
    }
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int k;
            cin >> k;
            int ls = -1;
            for (int j = 0; j < k; ++j) ls = add();
            cout << ls + 1 << endl;
        } else {
            int x;
            cin >> x;
            --x;
            int y = get(x);
            del(y);
            cout << h[x] - h[y] << endl;
        }
    }
    return 0;
}
