#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 1, LN = 18;
vector<int> g[MAX];
int h[MAX];
int up[MAX][LN];

void dfs(int v, int p = 0) {
    h[v] = h[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        dfs(to, v);
    }
}

int cnt[MAX];
const int INF = 1e9;

int dfs2(int v, int m) {
    int sum = (h[v] > m);
    for (int to : g[v]) {
        int ex = dfs2(to, m);
        if (ex < 0) {
            return -INF;
        }
        sum += ex;
    }
    //cout << v << " " << m << " " << sum - cnt[v] << endl;
    return sum - cnt[v];
}

int upp(int v, int u) {
    for (int i = 0; i < LN; ++i) {
        if ((u >> i) & 1) {
            v = up[v][i];
        }
    }
    return v;
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[p].push_back(i);
    }
    h[0] = -1;
    dfs(0, 0);
    vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
        --a[i];
        a[i] = upp(a[i], (h[a[i]] - 1) / 2);
        cnt[a[i]]++;
        //cout << h[a[i]] << " " << a[i] << endl;
    }
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (dfs2(0, m) >= 0) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l + 2 << endl;
    return 0;
}
