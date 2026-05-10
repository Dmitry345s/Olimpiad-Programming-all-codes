#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5 + 2;
vector<vector<pair<int, int>>> tree(4 * MAX);
vector<int> ans(MAX);

void put(int v, int l, int r, int ql, int qr, pair<int, int> pr) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].push_back(pr);
        return;
    }
    int m = (l + r) / 2;
    put(2 * v, l, m, ql, qr, pr);
    put(2 * v + 1, m, r, ql, qr, pr);
}

vector<int> p(MAX), sz(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return root(p[v]);
}

pair<int, int> unite(int v, int u) {
    int rv = root(v);
    int ru = root(u);
    if (rv == ru) {
        return {-1, -1};
    }
    if (sz[rv] < sz[ru]) {
        swap(rv, ru);
    }
    p[ru] = rv;
    sz[rv] += sz[ru];
    return {rv, ru};
}

void split(int v, int u) {
    p[u] = u;
    sz[v] -= sz[u];
}

void to_ans(int v, int l, int r, int now) {
    vector<pair<int, int>> all;
    for (auto [a, b] : tree[v]) {
        all.push_back(unite(a, b));
        if (all.back().first != -1) {
            now--;
        }
    }
    int m = (l + r) / 2;
    if (l + 1 == r) {
        ans[l] = now;
    } else {
        to_ans(2 * v, l, m, now);
        to_ans(2 * v + 1, m, r, now);
    }
    reverse(all.begin(), all.end());
    for (auto [a, b] : all) {
        if (a == -1) continue;
        split(a, b);
        now++;
    }
}

signed main() {
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<int> ch(q);
    map<pair<int, int>, vector<int>> mp;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '?') {
            ch[i] = 1;
        } else {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if (a > b) {
                swap(a, b);
            }
            mp[{a, b}].push_back(i);
        }
    }
    for (auto [key, val] : mp) {
        if ((int)val.size() % 2 == 1) {
            val.push_back(q);
        }
        for (int i = 0; i < (int)val.size(); i += 2) {
            put(1, 0, q + 1, val[i], val[i + 1], key);
        }
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    to_ans(1, 0, q + 1, n);
    for (int i = 0; i < q; ++i) {
        if (ch[i]) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
