#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 1;
string s;
string t;
int dpp[MAX], dps[MAX];
int flag = 0;
vector<int> g[MAX];

void dfs(int v, int p) {
    set<pair<int, int>> suf;
    dpp[v] = (t[0] == s[v]);
    dps[v] = (t.back() == s[v]);
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        suf.insert({-dps[to], to});
        if (dpp[to] < (int)t.size()) {
            dpp[v] = max(dpp[v], dpp[to] + (t[dpp[to]] == s[v]));
        } else {
            dpp[v] = dpp[to];
        }
        if (dps[to] < (int)t.size()) {
            dps[v] = max(dps[v], dps[to] + (t[(int)t.size() - 1 - dps[to]] == s[v]));
        } else {
            dps[v] = dps[to];
        }
    }
    if (dpp[v] == (int)t.size() || dps[v] == (int)t.size()) flag = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        suf.erase({-dps[to], to});
        int x = 0;
        if (dpp[to] < (int)t.size()) {
            x = max(x, dpp[to] + (t[dpp[to]] == s[v]));
        } else {
            x = dpp[to];
        }
        int y = -(suf.begin()->first);
        if (x + y >= (int)t.size()) {
            flag = 1;
        }
        suf.insert({-dps[to], to});
    }
}

signed main() {
    int _;
    cin >>_;
    while (_--) {
        int n;
        cin >> n;
        cin >> s;
        for (int i = 0; i < n; ++i) {
            dpp[i] = 0;
            dps[i] = 0;
            g[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        cin >> t;
        flag = 0;
        dfs(0, 0);
        if (flag) {
            cout << ":)" << endl;
        } else {
            cout << ":(" << endl;
        }
    }
    return 0;
}
