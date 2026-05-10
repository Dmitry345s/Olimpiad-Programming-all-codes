#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 2, LN = 18;
vector<vector<int>> g(MAX), up(MAX, vector<int> (LN));
vector<int> dpst(MAX, -1);
vector<int> deep(MAX);

void dfs(int v = 0, int p = 0) {
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    int mn = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        if (deep[to] > mn) {
            mn = deep[to];
            dpst[v] = to;
        }
    }
    if (dpst[v] == -1) {
        deep[v] = 1;
    } else {
        deep[v] = deep[dpst[v]] + 1;
    }
}

vector<int> used(MAX, -1);
vector<int> used2(MAX, -1);
vector<vector<int>> path;

void dfs2(int v = 0, int p = 0) {
    //cout << v << " " << dpst[v] << endl;
    if (dpst[v] != -1) {
        dfs2(dpst[v], v);
    }
    used[v] = (int)path.size() - 1;
    used2[v] = (int)path.back().size();
    path.back().push_back(v);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    vector<int> cnt(n + 1);
    cnt[1] = 0;
    for (int i = 2; i <= n; ++i) {
        cnt[i] = cnt[i - 1];
        if ((1ll << (cnt[i] + 1)) <= i) {
            cnt[i]++;
        }
        //cout << cnt[i] << endl;
    }
    dfs();
    //cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1) {
            path.push_back({});
            dfs2(i);
        }
    }
    //cout << 1 << endl;
    for (int i = 0; i < (int)path.size(); ++i) {
        int v = path[i].back();
        int sz = path[i].size();
        for (int j = 0; j < sz; ++j) {
            path[i].push_back(up[v][0]);
            v = up[v][0];
        }
    }
    int a1, a2;
    int x, y, z;
    cin >> a1 >> a2;
    cin >> x >> y >> z;
    int v = 0;
    long long rans = 0;
    for (int i = 0; i < m; ++i) {
        int now1 = (a1 + v) % n, now2 = a2;
        int bin = up[now1][cnt[now2]];
        //cout << used[bin] << " " << used2[bin] << endl;
        if (now2 == 0) {
            v = now1;
        } else if (used2[bin] + now2 - (1 << cnt[now2]) > (int)path[used[bin]].size() - 1) {
            v = 0;
        } else {
            v = path[used[bin]][used2[bin] + now2 - (1 << cnt[now2])];
        }
        rans += v;
        a1 = (1ll * x * a1 + 1ll * y * a2 + z) % n;
        a2 = (1ll * x * a2 + 1ll * y * a1 + z) % n;
    }
    cout << rans << endl;
    return 0;
}
