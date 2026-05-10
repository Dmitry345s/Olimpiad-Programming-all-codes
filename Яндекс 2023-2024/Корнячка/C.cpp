#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5;
vector<unordered_set<int>> ch(MAX);
vector<vector<int>> g(MAX);

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        ch[a].insert(b);
        ch[b].insert(a);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        sort(g[i].rbegin(), g[i].rend());
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (to <= i) break;
            if ((int)g[i].size() > (int)g[to].size()) {
                for (int to2 : g[to]) {
                    if (ch[i].find(to2) != ch[i].end()) {
                        ans++;
                        //cout << i << " " << to << " " << to2 << endl;
                    }
                }
            } else {
                for (int to2 : g[i]) {
                    if (ch[to].find(to2) != ch[to].end()) {
                        ans++;
                        //cout << i << " " << to << " " << to2 << endl;
                    }
                }
            }
        }
    }
    cout << ans / 3 << endl;
    return 0;
}
