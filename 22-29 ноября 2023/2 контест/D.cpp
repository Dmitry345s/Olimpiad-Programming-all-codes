#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 3e3;
vector<vector<pair<int, int>>> g(MAX);
set<int> st;
vector<int> a(MAX);
vector<int> used(MAX);

void dfs(int v, int w) {
    used[v] = 1;
    a[v] += w;
    for (auto [to, i] : g[v]) {
        if (st.find(i) != st.end() || used[to]) continue;
        dfs(to, w);
    }
}

int ans = 0, ans2 = 0;

void dfs2(int v) {
    used[v] = 1;
    ans += a[v];
    ans2 += 1;
    for (auto [to, i] : g[v]) {
        if (st.find(i) != st.end() || used[to]) continue;
        dfs2(to);
    }
}

void dfs3(int v) {
    used[v] = 1;
    ans += a[v];
    a[v] = 0;
    for (auto [to, i] : g[v]) {
        if (st.find(i) != st.end() || used[to]) continue;
        dfs3(to);
    }
}

vector<vector<int>> fnew(3e5), fnew2(3e5);
vector<pair<int, int>> ch(3e5);

void dfs4(int v, int num) {
    used[v] = 1;
    fnew[num].push_back(v);
    ch[v] = {num, fnew.size() - 1};
    fnew2[num].push_back(a[v]);
    for (auto [to, i] : g[v]) {
        if (st.find(i) != st.end() || used[to]) continue;
        dfs4(to, num);
    }
}

vector<vector<int>> trees(3e5);
vector<vector<int>> uptr(3e5);
vector<vector<int>> uptr2(3e5);

void push(int v, int i, int l, int r) {
    int m = (l + r) / 2;
    if (uptr[i][v] != -1) {
        uptr[i][2 * v] = 0;
        trees[i][2 * v] = 0;
        uptr[i][2 * v + 1] = 0;
        trees[i][2 * v + 1] = 0;
        uptr[i][v] = -1;
    } else {
        trees[i][2 * v] += uptr2[i][v] * (m - l);
        trees[i][2 * v + 1] += uptr2[i][v] * (r - m);
        uptr2[i][2 * v] += uptr2[i][v];
        uptr2[i][2 * v + 1] += uptr2[i][v];
        uptr2[i][v] = 0;
    }
}

void build(int v, int l, int r, int i) {
    if (l + 1 == r) {
        trees[i][v] = fnew2[i][l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, i);
    build(2 * v + 1, m, r, i);
}

void update1(int v, int l, int r, int i, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        uptr[i][v] = 0;
        trees[i][v] = 0;
        return;
    }
    push(v, i, l, r);
    int m = (l + r) / 2;
    update1(2 * v, l, m, i, ql, qr);
    update1(2 * v + 1, m, r, i, ql, qr);
    trees[i][v] = trees[i][2 * v] + trees[i][2 * v + 1];
}

void update2(int v, int l, int r, int i, int ql, int qr, int d) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        uptr2[i][v] = d;
        trees[i][v] += d * (r - l);
        return;
    }
    push(v, i, l, r);
    int m = (l + r) / 2;
    update2(2 * v, l, m, i, ql, qr, d);
    update2(2 * v + 1, m, r, i, ql, qr, d);
    trees[i][v] = trees[i][2 * v] + trees[i][2 * v + 1];
}

int get(int v, int l, int r, int i, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return trees[i][v];
    }
    push(v, i, l, r);
    int m = (l + r) / 2;
    return get(2 * v, l, m, i, ql, qr) + get(2 * v + 1, m, r, i, ql, qr);
}

signed main() {
    int h;
    cin >> h;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    for (int i = 0; i < n - 1; ++i) {
        char ch;
        cin >> ch;
        if (ch == '1') {
            st.insert(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (h == 6) {
        for (int i = 0; i < m; ++i) {
            int t;
            cin >> t;
            if (t == 2) {
                int p, w;
                cin >> p >> w;
                p--;
                auto [j, num] = ch[p];
                update2(1, 0, fnew2[j].size(), j, 0, fnew2[j].size(), w);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            cin >> p;
            --p;
            if (st.find(p) == st.end()) {
                st.insert(p);
            } else {
                st.erase(p);
            }
        } else if (t == 2) {
            used.assign(MAX, 0);
            int p, w;
            cin >> p >> w;
            --p;
            dfs(p, w);
        } else if (t == 3) {
            used.assign(MAX, 0);
            ans = 0;
            int p;
            cin >> p;
            --p;
            dfs3(p);
            a[p] = ans;
        } else if (t == 4) {
            int p;
            cin >> p;
            --p;
            cout << a[p] << endl;
        } else if (t == 5) {
            int p;
            cin >> p;
            --p;
            ans = 0;
            used.assign(MAX, 0);
            dfs2(p);
            cout << ans << endl;
        } else if (t == 6) {
            used.assign(MAX, 0);
            ans = 0;
            int p;
            cin >> p;
            --p;
            dfs3(p);
        } /*else {
            int cnt = 0;
            used.assign(MAX, 0);
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    ans = 0;
                    dfs2(i);
                    if (ans != 0) {
                        cnt++;
                    }
                }
            }
            cout << max(1ll * 0, cnt - 1) << endl;
        }*/
    }
    return 0;
}
