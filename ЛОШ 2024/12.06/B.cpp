#include<bits/stdc++.h>

using namespace std;
using ll = long long;

int MAX = 3e5, ln = 19;
vector<vector<pair<int, ll>>> g(MAX);
vector<vector<pair<int, long long>>> edges(MAX);
vector<int> used(MAX);
vector<array<long long, 3>> dp(MAX, {(ll)1e18, (ll)1e18, (ll)1e18});
vector<vector<int>> up(ln, vector<int> (MAX));
vector<ll> h(MAX), tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p = 0, ll del = 0) {
    up[0][v] = p;
    h[v] = h[p] + del;
    tin[v] = timer++;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        dfs(to, v, c);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = ln - 1; i >= 0; --i) {
        if (!(ch(up[i][a], b))) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

void dfs2(int v, int p = 0) {
    if (used[v] == 1) {
        dp[v][1] = 0;
    } else if (used[v] == 2) {
        dp[v][2] = 0;
    }
    for (auto [to, c] : edges[v]) {
        if (to == p) continue;
        dfs2(to, v);
        dp[v][1] = min(dp[v][1], dp[to][1] + c);
        dp[v][2] = min(dp[v][2], dp[to][2] + c);
    }
    dp[v][0] = min(dp[v][0], dp[v][1] + dp[v][2]);
    //cout << "! " << v << " " << dp[v][1] << " " << dp[v][2] << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(0);
    for (int _ = 0; _ < q; ++_) {
        int s, t;
        cin >> s >> t;
        vector<int> all1(s), all2(t);
        vector<pair<int, int>> to;
        for (int i = 0; i < s; ++i) {
            int v;
            cin >> v;
            --v;
            all1.push_back(v);
            to.push_back({tin[v], v});
            used[v] = 1;
        }
        for (int i = 0; i < t; ++i) {
            int v;
            cin >> v;
            --v;
            all2.push_back(v);
            to.push_back({tin[v], v});
            used[v] = 2;
        }
        ll ans = 1e18;
        sort(to.begin(), to.end());
        vector<pair<int, int>> to2 = to;
        for (int i = 1; i < (int)to.size(); ++i) {
            int x = lca(to[i - 1].second, to[i].second);
            to2.push_back({tin[x], x});
        }
        to2.push_back({tin[0], 0});
        sort(to2.begin(), to2.end());
        to2.erase(unique(to2.begin(), to2.end()), to2.end());
        vector<int> st;
        for (int i = 0; i < (int)to2.size(); ++i) {
            while ((int)st.size() > 0 && tout[st.back()] < tout[to2[i].second]) {
                st.pop_back();
            }
            if ((int)st.size() > 0) {
                //cout << st.back() << " " << to2[i].second << " " << h[to2[i].second] - h[st.back()] << endl;
                edges[st.back()].push_back({to2[i].second, h[to2[i].second] - h[st.back()]});
                edges[to2[i].second].push_back({st.back(), h[to2[i].second] - h[st.back()]});
            }
            st.push_back(to2[i].second);
        }
        dfs2(0);
        for (int i = 0; i < (int)to2.size(); ++i) {
            used[to2[i].second] = 0;
            edges[to2[i].second].clear();
            ans = min(ans, dp[to2[i].second][0]);
            dp[to2[i].second] = {(ll)1e18, (ll)1e18, (ll)1e18};
        }
        cout << ans << endl;
    }
    return 0;
}
