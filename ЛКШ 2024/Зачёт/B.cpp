#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5, LN = 20;
vector<int> g[MAX];
int up[MAX][LN];
vector<int> ch[MAX];
int tin[MAX], tout[MAX];
int timer = 0;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool check(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (check(a, b)) return a;
    if (check(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!check(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

multiset<int> st;
int ans = 0;

void dfs2(int v, int p) {
    for (int to : g[v]) {
        if (to == p) continue;
        int sz = (int)st.size();
        dfs2(to, v);
        if (sz == (int)st.size()) {
            ans++;
        }
    }
    for (int now : ch[v]) {
        if (now > 0) {
            st.insert(now);
        } else {
            st.erase(-now);
        }
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int x = lca(a, b);
        //cout << x << endl;
        ch[a].push_back(i + 1);
        ch[b].push_back(i + 1);
        ch[x].push_back(-i - 1);
    }
    dfs2(0, 0);
    cout << ans << endl;
    return 0;
}
/*
7
1 2
2 3
2 4
5 2
5 6
7 5
3
1 7
2 4
7 6*/
