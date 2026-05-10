#include<bits/stdc++.h>
//#define GLIBCXX__ DEBUG
#define int long long

using namespace std;

const int MAX = 2e5, INF = 2e9;
pair<int, int> tree[2 * MAX];

void upd(int in, int x) {
    int v = in + MAX;
    tree[v].first = x;
    while (v > 1) {
        v /= 2;
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
}

int get() {
    return tree[1].second;
}

int s[MAX];

bool cmp(int a, int b) {
    if (s[a] == s[b]) return a < b;
    return s[a] < s[b];
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 2 * MAX - 1; i >= MAX; --i) {
        tree[i] = {INF, i - MAX};
    }
    for (int i = MAX - 1; i >= 0; --i) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }
    int mxs = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        mxs = max(mxs, s[i]);
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end(), cmp);
    }
    vector<int> ans(n);
    int c = min(mxs * 2, n);
    vector<int> us(n);
    for (int st = 0; st < n; ++st) {
        vector<int> now;
        now.push_back(st);
        us[st] = 1;
        upd(st, INF);
        while ((int)now.size() < c) {
            int v = now.back();
            int cnt = 0;
            for (int j = 0; j < (int)g[v].size() && cnt < c; ++j) {
                int to = g[v][j];
                if (!us[to]) {
                    upd(to, s[to]);
                    cnt++;
                }
            }
            int nv = get();
            now.push_back(nv);
            us[nv] = 1;
            upd(nv, INF);
        }
        for (int in : now) {
            us[in] = 0;
        }
        if (s[now[0]] < s[now[1]]) {
            cout << -1 << " ";
            continue;
        }
        int ans = 0;
        int pref = s[now[0]] + s[now[1]];
        for (int i = 2; i < (int)now.size(); ++i) {
            int del = s[now[i]];
            ans = max(ans, (del - pref + i - 2) / (i - 1));
            pref += del;
        }
        while (tree[1].first < INF) {
            upd(get(), INF);
        }
        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
