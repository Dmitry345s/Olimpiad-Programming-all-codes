#include<bits/stdc++.h>

using namespace std;

const int MAX = 25e3 + 1;
int p[MAX];
vector<unsigned int> minm(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

void unite(int v, int u) {
    //if (sz[v] < sz[u]) {
        //swap(u, v);
    //}
    p[u] = v;
    //sz[v] += sz[u];
    //minm[v] = max(minm[v], minm[u]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (true) {
        unsigned int n, m, a, b;
        cin >> n >> m >> a >> b;
        if (n == 0) break;
        vector<unsigned int> all(n);
        for (int i = 0; i < n; ++i) {
            all[i] = (1ll * a * (i + 1) + b);
            //if (i >= n) continue;
            //cout << all[i] << endl;
        }
        vector<vector<int>> wh(n);
        for (int i = n; i < n + 2 * m; i += 2) {
            unsigned int l = (1ll * a * (i + 1) + b);
            unsigned int r = (1ll * a * (i + 2) + b);
            //cout << l << " " << r << endl;
            wh[max(l % n, r % n)].push_back(min(l % n, r % n));
        }
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            //sz[i] = 1;
            //minm[i] = i;
        }
        vector<pair<int, unsigned int>> st;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            while ((int)st.size() >= 1 && st.back().second >= all[i]) {
                unite(i, st.back().first);
                st.pop_back();
            }
            st.push_back({i, all[i]});
            //cout << "!" << " " << st.size() << endl;
            for (int j = 0; j < (int)wh[i].size(); ++j) {
                //cout << i << " " << wh[i][j] << " " << root(wh[i][j]) << endl;
                ans += all[root(wh[i][j])];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
