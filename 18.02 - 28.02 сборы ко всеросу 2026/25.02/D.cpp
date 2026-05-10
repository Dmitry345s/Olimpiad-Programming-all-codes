#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 100005;
vector<int> g1[MAX];
vector<int> g2[MAX];

vector<int> l1;
vector<int> l2;

void dfs1(int v, int p) {
    l1.push_back(v);
    for (int to : g1[v]) {
        if (to == p) continue;
        dfs1(to, v);
    }
}

int sz[MAX];
int tin[MAX];
int timer = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    tin[v] = timer++;
    for (int to : g2[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
}

int tree[2 * MAX];

void build(int n) {
    for (int i = 1; i < 2 * n; ++i) tree[i] = 0;
}

int get(int n, int l, int r) {
    l += n;
    r += n;
    int ans = 0;
    while (l < r) {
        if (l % 2) {
            ans += tree[l];
            l += 1;
        }
        l /= 2;
        if (r % 2) {
            ans += tree[r - 1];
        }
        r /= 2;
    }
    return ans;
}

void upd(int n, int in, int x) {
    int v = n + in;
    while (v >= 1) {
        tree[v] += x;
        v /= 2;
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g1[u].push_back(v);
        g1[v].push_back(u);
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g2[u].push_back(v);
        g2[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        if ((int)g1[i].size() == 1) {
            dfs1(i, i);
            break;
        }
    }
    dfs(0, 0);
    vector<vector<int>> interl(n);
    vector<vector<int>> interr(n);
    int all = 0;
    for (int i = 0; i < n; ++i) {
        int b = l1[i];
        int nsum = 0;
        for (int to : g2[b]) {
            if (tin[to] < tin[b]) continue;
            interl[b].push_back(get(n, tin[to], tin[to] + sz[to]));
            nsum += interl[b].back();
        }
        interl[b].push_back(all - nsum);
        all++;
        upd(n, tin[b], 1);
    }
    all = 0;
    build(n);
    for (int i = n - 1; i >= 0; --i) {
        int b = l1[i];
        int nsum = 0;
        for (int to : g2[b]) {
            if (tin[to] < tin[b]) continue;
            interr[b].push_back(get(n, tin[to], tin[to] + sz[to]));
            nsum += interr[b].back();
        }
        interr[b].push_back(all - nsum);
        all++;
        upd(n, tin[b], 1);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int ysum = 0;
        for (int nsum : interr[i]) {
            ysum += nsum;
        }
        for (int j = 0; j < (int)g2[i].size(); ++j) {
            ans += 2 * interl[i][j] * (ysum - interr[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}
