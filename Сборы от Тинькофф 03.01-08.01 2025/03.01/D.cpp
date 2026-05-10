#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 1;
int K = 2000;
int p[MAX];
int cl[MAX];
int sz[MAX];
int ch[MAX];
int cnt = 0;
pair<int, int> all[2 * MAX];
vector<array<int, 3>> qs[2 * MAX];

pair<int, int> root(int v) {
    if (p[v] == v) {
        return {v, cl[v]};
    }
    auto [rt, c] = root(p[v]);
    return {rt, (c ^ cl[v])};
}

vector<array<int, 3>> pred;

void unite(int v, int u) {
    auto [ru, cu] = root(u);
    auto [rv, cv] = root(v);
    if (ru == rv) {
        pred.push_back({rv, ru, ch[ru]});
        if (cu == cv) {
            ch[rv] += 1;
            cnt += 1;
        }
        return;
    }
    if (sz[ru] > sz[rv]) {
        swap(ru, rv);
        swap(u, v);
    }
    pred.push_back({ru, rv, cl[ru]});
    if (cu == cv) {
        cl[ru] ^= 1;
    }
    p[ru] = rv;
    sz[rv] += sz[ru];
}

void del() {
    if (pred.empty()) return;
    auto [u, v, trt] = pred.back();
    if (u != v) {
        p[u] = u;
        sz[v] -= sz[u];
        cl[u] = trt;
    } else {
        cnt -= ch[u];
        ch[u] = trt;
        cnt += ch[u];
    }
    pred.pop_back();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    if (q <= 2000) {
        K = 3000;
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        all[i] = {u, v};
        all[i + m] = {u, v};
    }
    vector<array<int, 3>> just;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        swap(l, r);
        r += m;
        l++;
        r--;
        //cout << l << " " << r << endl;
        if (r - l + 1 <= K) {
            just.push_back({l, r, i});
        } else {
            qs[r / K].push_back({l, r, i});
        }
    }
    vector<int> ans(q);
    for (int i = 2 * m - 1; i >= 0; --i) {
        if (qs[i].empty()) continue;
        sort(qs[i].rbegin(), qs[i].rend());
        int rl = (i) * K;
        int rr = (i) * K;
        for (auto [l, r, in] : qs[i]) {
            int cntt = 0;
            while (rl > l) {
                rl--;
                auto [u, v] = all[rl];
                unite(u, v);
            }
            while (rr <= r) {
                cntt++;
                auto [u, v] = all[rr];
                unite(u, v);
                rr++;
            }
            if (cnt > 0) {
                ans[in] = 1;
            }
            while (cntt) {
                del();
                cntt--;
                rr--;
            }
        }
        while (rl < (i) * K) {
            ++rl;
            del();
        }
    }
    for (auto [l, r, in] : just) {
        for (int i = l; i <= r; ++i) {
            auto [u, v] = all[i];
            unite(u, v);
        }
        if (cnt > 0) {
            ans[in] = 1;
        }
        for (int i = l; i <= r; ++i) {
            del();
        }
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i]) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}
