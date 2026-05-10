#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5;
vector<vector<int>> g(MAX);
vector<int> all(MAX);
vector<int> used(MAX);
vector<int> cnt(MAX);
vector<int> ord;
vector<int> tin(MAX);
vector<int> sz(MAX);

void dfs(int v) {
    tin[v] = ord.size();
    ord.push_back(v);
    sz[v] = 1;
    for (int to : g[v]) {
        dfs(to);
        sz[v] += sz[to];
    }
}

vector<int> tree(4 * MAX);

void update(int v, int l, int r, int id, int x, int ch) {
    if (l + 1 == r) {
        if (ch == 0) {
            tree[v] = x;
        } else {
            tree[v] += x;
        }
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x, ch);
    } else {
        update(2 * v + 1, m, r, id, x, ch);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}


int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> p(n);
    p[0] = -1;
    for (int i = 1; i < n; ++i) {
        cin >> p[i];
        --p[i];
        g[p[i]].push_back(i);
    }
    dfs(0);
    int q;
    cin >> q;
    vector<int> l3(n);
    vector<int> l1(n);
    vector<int> ok(n);
    vector<set<int>> mcnt(n);
    vector<int> used(n);
    for (int i = 0; i < q; ++i) {
        int t, x;
        cin >> t >> x;
        --x;
        int in = tin[x];
        if (x != 0 && ok[x] < l3[p[x]]) {
            if (used[x] == 1) {
                update(1, 0, n, in, -1, 1);
            }
            if (used[x] == 1) {
                update(1, 0, n, tin[p[x]], 1, 1);
            }
            used[x] = 0;
            ok[x] = l3[p[x]];
        }
        if (t == 1) {
            ok[x] = i;
            if (!used[x]) {
                update(1, 0, n, in, 1, 1);
            }
            used[x] = 1;
            if (x != 0) {
                mcnt[p[x]].insert(x);
            }
        } else if (t == 4) {
            cout << get(1, 0, n, in, in + sz[x]) << endl;
        } else if (t == 3) {
            l3[x] = i;
            ok[x] = i;
            update(1, 0, n, in, -(int)mcnt[x].size() - used[x], 1);
            if (x != 0) {
                mcnt[p[x]].erase(x);
            }
            used[x] = 0;
            mcnt[x].clear();
        }
    }
    return 0;
}
