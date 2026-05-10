#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
int k = 350;
vector<int> used(MAX);
vector<int> p(MAX);
int num = 0;

vector<vector<int>> b;
vector<int> c(MAX);

void dfs(int v) {
    if (b.size() == 0 || (int)b[num].size() == k) {
        b.push_back({});
        num++;
    }
    c[v] = num;
    b[num].push_back(v);
    used[v] = 1;
    if (!used[p[v]]) {
        dfs(p[v]);
    }
}

void rebuild(int n) {
    b.clear();
    num = -1;
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            b.push_back({});
            num++;
            dfs(i);
        }
    }
}

void split(int x) {
    int u = c[x];
    int ch1 = (int)b.size(), ch2 = ch1 + 1;
    int rch = 0;
    vector<int> f, s;
    for (int i = 0; i < (int)b[u].size(); ++i) {
        if (!rch) {
            f.push_back(b[u][i]);
            c[b[u][i]] = ch1;
        } else {
            s.push_back(b[u][i]);
            c[b[u][i]] = ch2;
        }
        if (b[u][i] == x) {
            rch = 1;
        }
    }
    b.push_back(f); b.push_back(s);
}

int ans(int v, int k2) {
    int u = c[v];
    while (k2 > 0 && c[v] == u) {
        k2 -= 1;
        v = p[v];
    }
    while ((int)b[c[v]].size() <= k2) {
        k2 -= (int)b[c[v]].size();
        v = p[b[c[v]].back()];
    }
    while (k2 > 0) {
        k2 -= 1;
        v = p[v];
    }
    return v;
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
    for (int i = 0; i < q; ++i) {
        if (i % k == 0) {
            rebuild(n);
        }
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            split(x);
            split(y);
            swap(p[x], p[y]);
        } else {
            int i, k2;
            cin >> i >> k2;
            --i;
            cout << ans(i, k2) + 1 << endl;
        }
    }
    return 0;
}
