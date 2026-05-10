#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 5;
int w[MAX], tin[MAX], tout[MAX], sz[MAX], head[MAX], pr[MAX];
vector<int> g[MAX];
vector<int> ord;
int timer = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
}

bool cmp(int a, int b) {
    if (sz[a] == sz[b]) {
        return a < b;
    }
    return sz[a] > sz[b];
}

void dfs2(int v, int p, int now) {
    sort(g[v].begin(), g[v].end(), cmp);
    int flag = 0;
    head[v] = now;
    tin[v] = timer++;
    pr[v] = p;
    ord.push_back(v);
    for (int to : g[v]) {
        if (to == p) continue;
        if (!flag) {
            dfs2(to, v, now);
            flag = 1;
        } else {
            dfs2(to, v, to);
        }
    }
    tout[v] = timer;
}

int w2[MAX];
long long pref[MAX];
int tree[4 * MAX], update_tree[4 * MAX];

void push(int v, int l, int r) {
    int m = (l + r) / 2;
    int x = update_tree[v];
    update_tree[v] = 0;
    tree[2 * v] += (pref[m] - pref[l]) * x;
    tree[2 * v + 1] += (pref[r] - pref[m]) * x;
    update_tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        long long del = pref[r] - pref[l];
        tree[v] += del * x;
        update_tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

long long get(int v, int l, int r, int ql, int qr) {
    //cout << "# " << v << " " << l << " " << r << " " << ql << " " << qr << endl;
    if (r <= ql || qr <= l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    push(v, l, r);
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

bool is_pr(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

long long rget(int v, int u, int n) {
    long long ans = 0;
    for (int i = 0; i < 2; ++i) {
        while (!is_pr(head[v], u)) {
            //cout << v << " " << ans << " " << head[v] << endl;
            ans += get(1, 0, n, tin[head[v]], tin[v] + 1);
            v = head[v];
            v = pr[v];
        }
        swap(v, u);
    }
    //cout << tin[v] << " " << tin[u] << endl;
    long long x = get(1, 0, n, min(tin[u], tin[v]), max(tin[v], tin[u]) + 1);
    //cout << x << endl;
    return x + ans;
}

void rupdate(int v, int u, int x, int n) {
    for (int i = 0; i < 2; ++i) {
        while (!is_pr(head[v], u)) {
            update(1, 0, n, tin[head[v]], tin[v] + 1, x);
            v = head[v];
            v = pr[v];
        }
        swap(v, u);
    }
    update(1, 0, n, min(tin[u], tin[v]), max(tin[v], tin[u]) + 1, x);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
            g[i].clear();
        }
        for (int i = 1; i < n; ++i) {
            int p;
            cin >> p;
            --p;
            g[i].push_back(p);
            g[p].push_back(i);
        }
        ord.clear();
        timer = 0;
        dfs(0, 0);
        dfs2(0, 0, 0);
        for (int i = 0; i < n; ++i) {
            //cout << ord[i] << " ";
        }
        //cout << endl;
        w2[0] = w[0];
        for (int i = 1; i < n; ++i) {
            w2[i] = w[i] - w[pr[i]];
            //cout << w2[i] << " ";
        }
        //cout << endl;
        pref[0] = 0;
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1] + w2[ord[i - 1]];
            //cout << pref[i] << " ";
        }
        //cout << endl;
        vector<long long> ans(n);
        fill(tree, tree + 4 * n, 0);
        fill(update_tree, update_tree + 4 * n, 0);
        for (int i = 0; i < n; ++i) {
            ans[i] = rget(i, 0, n);
            rupdate(i, 0, 1, n);
        }
        for (int i = 1; i < n; ++i) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
