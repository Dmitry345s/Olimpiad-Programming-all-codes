#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int MAX = 2e5, K = 90;
int opt[MAX];
int p[MAX];
int sz[MAX];
int cnt;

int root(int v) {
    while (v != p[v]) v = p[v];
    return v;
}

vector<pair<int, int>> last;

void unite(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    if (sz[u] > sz[v]) swap(u, v);
    last.push_back({v, u});
    p[u] = v;
    sz[v] += sz[u];
    cnt--;
}

void do_back() {
    auto [v, u] = last.back();
    p[u] = u;
    sz[v] -= sz[u];
    cnt++;
    last.pop_back();
}

int root2(int v) {
    if (v == p[v]) return v;
    return p[v] = root2(p[v]);
}

void unite2(int u, int v) {
    u = root2(u);
    v = root2(v);
    if (u == v) return;
    if (sz[u] > sz[v]) swap(u, v);
    p[u] = v;
    sz[v] += sz[u];
    cnt--;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> ed(m);
    for (int i = 0; i < m; ++i) {
        cin >> ed[i].first >> ed[i].second;
        --ed[i].first; --ed[i].second;
    }
    fill(opt, opt + m, -1);
    for (int i = K - 1; i < m; i += K) {
        fill(sz, sz + n, 1);
        iota(p, p + n, 0);
        cnt = n;
        opt[i] = i;
        while (cnt > 1 && opt[i] > -1) {
            unite2(ed[opt[i]].first, ed[opt[i]].second);
            opt[i]--;
        }
        if (cnt > 1) {
            opt[i] = -1;
        } else {
            opt[i]++;
        }
    }
    fill(sz, sz + n, 1);
    iota(p, p + n, 0);
    cnt = n;
    if (n - 1 < K) {
        for (int i = 0; i < m; ++i) {
            if (i % K == K - 1) continue;
            opt[i] = i;
            while (cnt > 1 && opt[i] > i / K * K - 1) {
                unite(ed[opt[i]].first, ed[opt[i]].second);
                opt[i]--;
            }
            if (cnt > 1) {
                opt[i] = -1;
            } else {
                opt[i]++;
            }
            while (!last.empty()) do_back();
        }
    }
    for (int i = K - 1; i < m; i += K) {
        fill(sz, sz + n, 1);
        iota(p, p + n, 0);
        cnt = n;
        int kk = max(-1, i - n + K + 1);
        if (i + K < m) {
            kk = min(kk, opt[i + K]);
        }
        if (kk == -1) continue;
        int now = i;
        while (now >= kk) {
            auto [u, v] = ed[now];
            unite2(u, v);
            now--;
        }
        while (now >= opt[i] - 1) {
            if (cnt <= K) {
                for (int j = i + 1; j < min(m, i + K); ++j) {
                    auto [u, v] = ed[j];
                    unite(u, v);
                    if (cnt == 1) {
                        if (opt[j] == -1) {
                            opt[j] = now + 1;
                        } else {
                            break;
                        }
                    }
                }
                while (!last.empty()) {
                    do_back();
                }
            }
            if (now < 0) break;
            unite2(ed[now].first, ed[now].second);
            now--;
        }
    }
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += opt[i] + 1;
    }
    cout << ans << '\n';
    return 0;
}
