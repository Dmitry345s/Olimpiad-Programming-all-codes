#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5;
vector<int> g[MAX];
int x[MAX];
int tr[MAX];
int fl = 1;

void dfs(int v, int p = 0) {
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        //cout << v << " " << to << " " << x[v] << " " << x[to] << " " << tr[to] << " " << tr[v] << endl;
        if (x[v] == 0) {
            if (x[to] == 1 && tr[to] == 0) {
                tr[to] = 1;
                tr[v] = 1;
            } else if (tr[to] == 0) {
                fl = 0;
            }
        } else {
            if (x[to] == 0 && tr[to] == 0) {
                if (tr[v] == 1) {
                    fl = 0;
                } else {
                    tr[v] = 1;
                    tr[to] = 1;
                }
            }
        }
    }
}

const int INF = 3e18;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ed(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
        ed[i] = {a, b};
    }
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        st.insert({x[i], i});
    }
    auto it = st.end();
    --it;
    int ans = (*it).first - (*st.begin()).first;
    for (int i = 0; i < n - 1; ++i) {
        auto [a, b] = ed[i];
        st.erase({x[a], a});
        st.erase({x[b], b});
        auto it = st.end();
        --it;
        auto it2 = st.begin();
        int mn = min((*it2).first, x[a] + x[b]);
        int mx = max((*it).first, x[a] + x[b]);
        ans = min(ans, mx - mn);
        st.insert({x[a], a});
        st.insert({x[b], b});
    }
    cout << ans << endl;
    return 0;
}
