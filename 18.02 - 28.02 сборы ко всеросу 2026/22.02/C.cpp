#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

//#define int long long

using namespace std;

const int MAX = 1e7 + 5;

const long long INF = 1e18;

int p[MAX];
long long mn[MAX];

int root(int v) {
    if (p[v] == v) return v;
    return p[v] = root(p[v]);
}

void unite(int u, int v) {
    u = root(u);
    v = root(v);
    p[v] = u;
    mn[u] = min(mn[u], mn[v]);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> h(m);
    vector<long long> c(m);
    vector<vector<int>> a(n);
    vector<vector<int>> yy(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int t;
            cin >> t;
            a[i].push_back(t);
        }
        for (int j = 0; j < k; ++j) {
            int t;
            cin >> t;
            yy[i].push_back(t);
        }
    }
    int q;
    cin >> q;
    int now = 0;
    for (int i = 0; i < q; ++i) {
        int id, mul;
        cin >> id >> mul;
        --id;
        for (int j = 0; j < (int)a[id].size(); ++j) {
            h[now + j] = a[id][j];
            c[now + j] = 1ll * yy[id][j] * mul;
        }
        now += (int)a[id].size();
    }
    /*for (int i = 0; i < m; ++i) {
        cout << h[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < m; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;*/
    vector<int> gol(m);
    vector<int> gor(m);
    vector<pair<int, int>> st;
    vector<int> pr(m);
    for (int i = 0; i < m; ++i) {
        pr[i] = max(0, i - h[i] + 1);
    }
    vector<int> tod(m, 0);
    for (int i = m - 1; i >= 0; --i) {
        while (!st.empty() && st.back().first >= pr[i]) {
            tod[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({pr[i], i});
    }
    gol[0] = 0;
    for (int i = 1; i < m; ++i) {
        gol[i] = i;
        if (tod[i] >= pr[i]) {
            gol[i] = gol[tod[i]];
        }
    }
    /*for (int i = 0; i < m; ++i) {
        cout << gol[i] << " ";
    }
    cout << endl;*/
    gor[m - 1] = m - 1;
    vector<int> nx(m);
    for (int i = 0; i < m; ++i) {
        nx[i] = min(m - 1, i + h[i] - 1);
    }
    vector<int> toup(m, m - 1);
    st.clear();
    for (int i = 0; i < m; ++i) {
        while (!st.empty() && st.back().first <= nx[i]) {
            toup[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({nx[i], i});
    }
    for (int i = m - 2; i >= 0; --i) {
        gor[i] = i;
        if (toup[i] <= nx[i]) {
            gor[i] = gor[toup[i]];
        }
    }
    /*for (int i = 0; i < m; ++i) {
        cout << gor[i] << " ";
    }
    cout << endl;*/
    long long dp[m + 1];
    fill(dp, dp + m + 1, INF);
    dp[0] = 0;
    mn[0] = 0;
    p[0] = 0;
    for (int i = 0; i < m; ++i) {
        dp[gor[i] + 1] = min(dp[gor[i] + 1], dp[i] + c[i]);
        int now = i;
        long long gtmn = INF;
        while (now >= gol[i]) {
            int rt = root(now);
            gtmn = min(gtmn, mn[rt]);
            if (rt > gol[i]) unite(rt - 1, rt);
            now = rt - 1;
        }
        dp[i + 1] = min(dp[i + 1], gtmn + c[i]);
        p[i + 1] = i + 1;
        mn[i + 1] = dp[i + 1];
    }
    cout << dp[m] << endl;
    return 0;
}
