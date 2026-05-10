#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;
vector<int> g[MAX];
int sz[MAX];
int wc[MAX];

void dfs(int v, int p, int szs, int & c) {
    sz[v] = 1;
    int maxm = 0;
    for (int to : g[v]) {
        if (to == p || wc[to] != -1) continue;
        dfs(to, v, szs, c);
        sz[v] += sz[to];
        maxm = max(maxm, sz[to]);
    }
    maxm = max(maxm, szs - sz[v]);
    if (maxm <= szs / 2) {
        c = v;
    }
}

void f_c(int v, int szs, int now) {
    int c;
    dfs(v, -1, szs, c);
    wc[c] = now;
    for (int to : g[c]) {
        if (wc[to] != -1) continue;
        int sz_to = sz[to];
        if (sz_to > sz[c]) {
            sz_to = szs - sz[c];
        }
        f_c(to, sz_to, now + 1);
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
    fill(wc, wc + n, -1);
    f_c(0, n, 0);
    for (int i = 0; i < n; ++i) {
        cout << (char)(wc[i] + 65) << " ";
    }
    cout << endl;
    return 0;
}
