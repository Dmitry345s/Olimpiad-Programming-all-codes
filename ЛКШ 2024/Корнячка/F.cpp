#include<bits/stdc++.h>

using namespace std;

const int K = 500, MAX = 1e5 + 5;
vector<int> sz(MAX);
vector<int> g[MAX];

bool cmp(int a, int b) {
    if (sz[a] == sz[b]) {
        return a > b;
    }
    return sz[a] > sz[b];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        sz[i] = (int)g[i].size();
    }
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end(), cmp);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (v[i] != v[to]) {
                ans++;
            }
        }
    }
    ans /= 2;
    vector<vector<int>> mp(n);
    for (int i = 0; i < n; ++i) {
        if (sz[i] > K) {
            mp[i].resize(MAX);
            for (int to : g[i]) {
                mp[i][v[to]]++;
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int c, vs;
        cin >> c >> vs;
        --c;
        if (sz[c] <= K) {
            for (int to : g[c]) {
                if (v[to] != v[c] && v[to] == vs) {
                    ans--;
                } else if (v[to] == v[c] && v[to] != vs) {
                    ans++;
                }
            }
            //cout << ans << endl;
        } else {
            ans += mp[c][v[c]];
            ans -= mp[c][vs];
        }
        //cout << ans << endl;
        for (int to : g[c]) {
            if (sz[to] > K) {
                mp[to][v[c]]--;
                mp[to][vs]++;
            } else {
                break;
            }
        }
        v[c] = vs;
        cout << ans << '\n';
    }
    return 0;
}
