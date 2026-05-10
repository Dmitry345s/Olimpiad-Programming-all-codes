#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e9 + 5;
vector<array<int, 4>> tree(1);

void update(int v, int l, int r, int in, int x1, int x2) {
    if (l + 1 == r) {
        tree[v][0] += x1;
        tree[v][1] += x2;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        if (tree[v][2] == -1) {
            tree.push_back({0, 0, -1, -1});
            tree[v][2] = (int)tree.size() - 1;
        }
        update(tree[v][2], l, m, in, x1, x2);
    } else {
        if (tree[v][3] == -1) {
            tree.push_back({0, 0, -1, -1});
            tree[v][3] = (int)tree.size() - 1;
        }
        update(tree[v][3], m, r, in, x1, x2);
    }
    tree[v][0] = 0;
    tree[v][1] = 0;
    if (tree[v][2] != -1) {
        tree[v][0] += tree[tree[v][2]][0];
        tree[v][1] += tree[tree[v][2]][1];
    }
    if (tree[v][3] != -1) {
        tree[v][0] += tree[tree[v][3]][0];
        tree[v][1] += tree[tree[v][3]][1];
    }
}

pair<int, int> get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return {0, 0};
    }
    if (ql <= l && r <= qr) {
        //cout << v << " " << l << " " << r << " " << tree[v][0] << " " << tree[v][1] << endl;
        return {tree[v][0], tree[v][1]};
    }
    int m = (l + r) / 2;
    if (tree[v][2] == -1) {
        tree.push_back({0, 0, -1, -1});
        tree[v][2] = (int)tree.size() - 1;
    }
    auto [ans1, ans2] = get(tree[v][2], l, m, ql, qr);
    if (tree[v][3] == -1) {
        tree.push_back({0, 0, -1, -1});
        tree[v][3] = (int)tree.size() - 1;
    }
    auto [ans3, ans4] = get(tree[v][3], m, r, ql, qr);
    return {ans1 + ans3, ans2 + ans4};
}

signed main() {
    int n, m;
    cin >> n >> m;
    if (m % 2 == 0) {
        m -= 1;
    }
    vector<int> h(n), g(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    vector<pair<int, int>> st;
    st.push_back({INF, -1});
    int now = 0;
    for (int i = 0; i < n; ++i) {
        while (st.back().first <= h[i]) {
            st.pop_back();
        }
        g[i] = st.back().second;
        now += i - g[i];
        st.push_back({h[i], i});
    }
    vector<vector<array<int, 4>>> inter(n);
    for (int i = 0; i < n; ++i) {
        inter[g[i] + 1].push_back({g[i], 1, h[i], i});
        inter[i].push_back({-g[i], -1, h[i], i});
    }
    tree[0] = {0, 0, -1, -1};
    set<pair<int, int>> mst;
    int ans = now;
    for (int i = 0; i < n - 1; ++i) {
        for (auto [dif1, dif2, hnow, in] : inter[i]) {
            update(0, 0, INF, hnow, dif1, dif2);
            //cout << hnow << " " << dif1 << " " << dif2 << endl;
            if (dif2 == 1) {
                mst.insert({-hnow, in});
            } else {
                mst.erase({-hnow, in});
            }
        }
        int mxh = min(h[i] + m, -(*mst.begin()).first + 1);
        pair<int, int> u = get(0, 0, INF, 0, mxh);
        auto it = mst.upper_bound({-mxh, INF});
        if (it == mst.end()) continue;
        //--it;
        int in = (*it).second;
        //cout << u.first << endl;
        int del = u.second * i - u.first;
        //cout << del << endl;
        ans = min(ans, now - del + i - g[in] - (i - g[i]));
        //cout << i << " " << mxh << " " << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
