//#define _GLIBCXX_DEBUG 1
#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long

using namespace std;

const int MAX = 1e5 + 1, INF = 1e9;
vector<int> a(MAX);
vector<int> ans(4 * MAX);
vector<vector<pair<int, int>>> treetol(4 * MAX);
vector<vector<pair<int, int>>> treetor(4 * MAX);

int mmerge(int v, int u, int k) {
    int tans = INF;
    long long need = (1ll << (k + 1)) - 2;
    long long maskv = 0, masku = 0;
    for (auto [in, x] : treetol[u]) {
        masku |= (1ll << x);
    }
    int l = (int)treetor[v].size() - 1;
    for (int r = (int)treetol[u].size() - 1; r >= 0; --r) {
        while (l >= 0 && ((maskv | masku) & need) != need) {
            maskv |= (1ll << treetor[v][l].second);
            l--;
        }
        if (((maskv | masku) & need) == need && l != (int)treetor[v].size() - 1) {
            tans = min(tans, treetol[u][r].first - treetor[v][l + 1].first + 1);
            ////cout << treeto[u][r].first << " " << treeto[v][l + 1].first << endl;
        }
        ////cout << v << " " << u << " " << maskv << " " << masku << endl;
        masku ^= (1ll << treetol[u][r].second);
    }
    return tans;
}

void build(int v, int l, int r, int k) {
    if (l + 1 == r) {
        if (a[l] == 1 && k == 1) {
            ans[v] = 1;
        } else {
            ans[v] = INF;
        }
        treetol[v] = {{l, a[l]}};
        treetor[v] = {{l, a[l]}};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, k);
    build(2 * v + 1, m, r, k);
    ans[v] = min(ans[2 * v], ans[2 * v + 1]);
    int y = mmerge(2 * v, 2 * v + 1, k);
    ans[v] = min(ans[v], y);
    vector<int> mask(k + 1);
    int rx = 0;
    treetol[v].clear();
    for (int lx = 0; lx < (int)treetol[2 * v].size(); ++lx) {
        while (rx < (int)treetol[2 * v + 1].size() && treetol[2 * v + 1][rx].first < treetol[2 * v][lx].first) {
            if (mask[treetol[2 * v + 1][rx].second] == 0) {
                treetol[v].push_back(treetol[2 * v + 1][rx]);
                mask[treetol[2 * v + 1][rx].second] = 1;
            }
            rx++;
        }
        if (mask[treetol[2 * v][lx].second] == 0) {
            treetol[v].push_back(treetol[2 * v][lx]);
            mask[treetol[2 * v][lx].second] = 1;
        }
    }
    while (rx < (int)treetol[2 * v + 1].size()) {
        if (mask[treetol[2 * v + 1][rx].second] == 0) {
            treetol[v].push_back(treetol[2 * v + 1][rx]);
            mask[treetol[2 * v + 1][rx].second] = 1;
        }
        rx++;
    }
    for (int i = 0; i <= k; ++i) {
        mask[i] = 0;
    }
    rx = (int)treetor[2 * v + 1].size() - 1;
    treetor[v].clear();
    for (int lx = (int)treetor[2 * v].size() - 1; lx >= 0; --lx) {
        while (rx >= 0 && treetor[2 * v + 1][rx].first > treetor[2 * v][lx].first) {
            if (mask[treetor[2 * v + 1][rx].second] == 0) {
                treetor[v].push_back(treetor[2 * v + 1][rx]);
                mask[treetor[2 * v + 1][rx].second] = 1;
            }
            rx--;
        }
        if (mask[treetor[2 * v][lx].second] == 0) {
            treetor[v].push_back(treetor[2 * v][lx]);
            mask[treetor[2 * v][lx].second] = 1;
        }
    }
    while (rx >= 0) {
        if (mask[treetor[2 * v + 1][rx].second] == 0) {
            treetor[v].push_back(treetor[2 * v + 1][rx]);
            mask[treetor[2 * v + 1][rx].second] = 1;
        }
        rx--;
    }
    reverse(treetor[v].begin(), treetor[v].end());
}

void update(int v, int l, int r, int in, int x, int k) {
    if (l + 1 == r) {
        if (x == 1 && k == 1) {
            ans[v] = 1;
        } else {
            ans[v] = INF;
        }
        treetol[v] = {{l, x}};
        treetor[v] = {{l, x}};
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x, k);
    } else {
        update(2 * v + 1, m, r, in, x, k);
    }
    ans[v] = min(ans[2 * v], ans[2 * v + 1]);
    int y = mmerge(2 * v, 2 * v + 1, k);
    ans[v] = min(ans[v], y);
    vector<int> mask(k + 1);
    int rx = 0;
    treetol[v].clear();
    for (int lx = 0; lx < (int)treetol[2 * v].size(); ++lx) {
        while (rx < (int)treetol[2 * v + 1].size() && treetol[2 * v + 1][rx].first < treetol[2 * v][lx].first) {
            if (mask[treetol[2 * v + 1][rx].second] == 0) {
                treetol[v].push_back(treetol[2 * v + 1][rx]);
                mask[treetol[2 * v + 1][rx].second] = 1;
            }
            rx++;
        }
        if (mask[treetol[2 * v][lx].second] == 0) {
            treetol[v].push_back(treetol[2 * v][lx]);
            mask[treetol[2 * v][lx].second] = 1;
        }
    }
    while (rx < (int)treetol[2 * v + 1].size()) {
        if (mask[treetol[2 * v + 1][rx].second] == 0) {
            treetol[v].push_back(treetol[2 * v + 1][rx]);
            mask[treetol[2 * v + 1][rx].second] = 1;
        }
        rx++;
    }
    for (int i = 0; i <= k; ++i) {
        mask[i] = 0;
    }
    rx = (int)treetor[2 * v + 1].size() - 1;
    treetor[v].clear();
    for (int lx = (int)treetor[2 * v].size() - 1; lx >= 0; --lx) {
        while (rx >= 0 && treetor[2 * v + 1][rx].first > treetor[2 * v][lx].first) {
            if (mask[treetor[2 * v + 1][rx].second] == 0) {
                treetor[v].push_back(treetor[2 * v + 1][rx]);
                mask[treetor[2 * v + 1][rx].second] = 1;
            }
            rx--;
        }
        if (mask[treetor[2 * v][lx].second] == 0) {
            treetor[v].push_back(treetor[2 * v][lx]);
            mask[treetor[2 * v][lx].second] = 1;
        }
    }
    while (rx >= 0) {
        if (mask[treetor[2 * v + 1][rx].second] == 0) {
            treetor[v].push_back(treetor[2 * v + 1][rx]);
            mask[treetor[2 * v + 1][rx].second] = 1;
        }
        rx--;
    }
    reverse(treetor[v].begin(), treetor[v].end());
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k, m;
    cin >> n >> k >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > k) {
            a[i] = 0;
        }
    }
    build(1, 0, n, k);
    ////cout << "!" << endl;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 2) {
            if (ans[1] != INF){
                cout << ans[1] << '\n';
            } else {
                cout << -1 << '\n';
            }
        } else {
            int in, x;
            cin >> in >> x;
            --in;
            if (x > k) {
                x = 0;
            }
            update(1, 0, n, in, x, k);
            a[in] = x;
        }
    }
    return 0;
}
