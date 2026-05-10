#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 100000;
vector<int> g1[MAX];
vector<int> g2[MAX];

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

void upd(int n, int l, int r, int x) {
    l += n;
    r += n;
    while (l < r) {
        if (l % 2) {
            tree[l] += x;
            l += 1;
        }
        l /= 2;
        if (r % 2) {
            tree[r - 1] += x;
        }
        r /= 2;
    }
}

int get(int n, int in) {
    int v = n + in;
    int sum = 0;
    while (v >= 1) {
        sum += tree[v];
        v /= 2;
    }
    return sum;
}

int ans = 0;

void coun(int v, int p, int n) {
    ans += get(n, tin[v]);
    if (v != p) upd(n, tin[v], tin[v] + sz[v], 1);
    for (int to : g1[v]) {
        if (to == p) continue;
        coun(to, v, n);
    }
    if (v != p) upd(n, tin[v], tin[v] + sz[v], -1);
}

int solve(int v, int n) {
    timer = 0;
    dfs(v, v);
    build(n);
    ans = 0;
    coun(v, v, n);
    //cout << "% " << v << " " << ans << endl;
    /*for (int i = 0; i < n; ++i) {
        cout << tin[i] << " " << sz[i] << endl;
    }*/
    return ans;
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
    int allans = 0;
    for (int i = 0; i < n; ++i) {
        allans += solve(i, n);
    }
    cout << allans << endl;
    return 0;
}
