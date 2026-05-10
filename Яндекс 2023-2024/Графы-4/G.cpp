#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10, ln = 20;
vector<int> g[MAX];
vector<int> all;
int h[MAX];
int gt[MAX];

void dfs(int v, int p) {
    h[v] = h[p] + 1;
    gt[v] = all.size();
    all.push_back(v);
    for (int to : g[v]) {
        dfs(to, v);
        all.push_back(v);
    }
}

pair<int, int> sparse[ln][2 * MAX];
int pows[ln], prp[2 * MAX];

void build() {
    int n = all.size();
    for (int i = 0; i < ln; ++i) {
        pows[i] = (1 << i);
    }
    prp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        prp[i] = prp[i / 2] + 1;
    }
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = {h[all[i]], i};
    }
    for (int i = 1; i < ln; ++i) {
        for (int j = 0; j < n; ++j) {
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][min(j + pows[i - 1], n - 1)]);
        }
    }
}

pair<int, int> get(int l, int r) {
    int sz = r - l + 1;
    return min(sparse[prp[sz]][l], sparse[prp[sz]][r - pows[prp[sz]] + 1]);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    h[0] = -1;
    dfs(0, 0);
    build();
    vector<int> a(2);
    cin >> a[0] >> a[1];
    int x, y, z;
    cin >> x >> y >> z;
    long long ans = 0;
    int last = 0;
    for (int i = 0; i < m; ++i) {
        int one = gt[(a[0] + last) % n], two = gt[a[1]];
        pair<int, int> u = get(min(one, two), max(one, two));
        //cout << x << endl;
        ans += all[u.second];
        last = all[u.second];
        a[0] = (1ll * x * a[0] + 1ll * a[1] * y + z) % n;
        a[1] = (1ll * x * a[1] + 1ll * a[0] * y + z) % n;
    }
    cout << ans << endl;
    return 0;
}
