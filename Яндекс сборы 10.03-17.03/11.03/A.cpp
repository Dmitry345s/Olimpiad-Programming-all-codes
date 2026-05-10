#include<bits/stdc++.h>

using namespace std;

vector<int> bfs(int n, vector<vector<int>> g, int v) {
    vector<int> d(n, n + 1);
    d[v] = 0;
    queue<int> q;
    q.push(v);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    return d;
}

const int MAX = 2e5 + 1;
int rused[MAX];

void rdfs(int v, int mxd, vector<int> & dist, vector<vector<int>> & g) {
    rused[v] = 1;
    for (int to : g[v]) {
        if (rused[to]) continue;
        if (dist[to] <= mxd && dist[to] == dist[v] + 1) {
            rdfs(to, mxd, dist, g);
        }
    }
}

int lused[MAX];

void ldfs(int v, int mnd, vector<int> & dist, vector<vector<int>> & g) {
    lused[v] = 1;
    for (int to : g[v]) {
        if (lused[to]) continue;
        if (dist[to] >= mnd && dist[to] == dist[v] - 1) {
            ldfs(to, mnd, dist, g);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, m, k, l;
        cin >> n >> m >> k >> l;
        vector<vector<int>> g(n);
        vector<int> s(k);
        for (int i = 0; i < k; ++i) cin >> s[i];
        for (int i = 0; i < k; ++i) s[i]--;
        vector<int> d(l);
        for (int i = 0; i < l; ++i) cin >> d[i];
        for (int i = 0; i < l; ++i) d[i]--;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<int> ndist = bfs(n, g, 0);
        vector<vector<int>> all(n);
        for (int i = 0; i < k; ++i) {
            all[ndist[s[i]]].push_back(s[i]);
        }
        int fl = 1;
        for (int i = 1; i < n; ++i) {
            if ((int)all[i].size() > 1) {
                fl = 0;
            }
        }
        vector<int> ans(n);
        vector<int> rall(n, -1);
        rall[0] = 0;
        int mxds = 0;
        for (int i = 1; i < n; ++i) {
            if (!all[i].empty()) {
                rall[i] = all[i][0];
                mxds = max(mxds, i);
            }
        }
        vector<pair<int, int>> nowg;
        for (int i = 0; i < n; ++i) {
            if (rall[i] != -1) {
                nowg.push_back({rall[i], i});
            }
        }
        fill(rused, rused + n, 0);
        fill(lused, lused + n, 0);
        for (int i = 0; i < (int)nowg.size() - 1; ++i) {
            rdfs(nowg[i].first, nowg[i + 1].second, ndist, g);
            if (!rused[nowg[i + 1].first]) fl = 0;
        }
        rdfs(nowg.back().first, n - 1, ndist, g);
        for (int i = 0; i < l; ++i) {
            if (ndist[d[i]] > mxds || ndist[d[i]] == mxds && rall[ndist[d[i]]] == d[i]) {
                ldfs(d[i], mxds, ndist, g);
            }
        }
        if (!lused[nowg.back().first]) fl = 0;
        for (int i = (int)nowg.size() - 2; i >= 0; --i) {
            ldfs(nowg[i + 1].first, nowg[i].second, ndist, g);
            if (!lused[nowg[i].first]) fl = 0;
        }
        for (int i = 0; i < n; ++i) {
            if (rall[ndist[i]] != -1 && rall[ndist[i]] != i) {
                lused[i] = 0;
                rused[i] = 0;
            }
        }
        if (fl == 0) {
            for (int i = 1; i < n; ++i) {
                cout << 0;
            }
            cout << endl;
            continue;
        }
        for (int i = 0; i < n; ++i) {
            if (lused[i] && rused[i]) {
                ans[i] = 1;
            }
        }
        for (int i = 1; i < n; ++i) {
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
