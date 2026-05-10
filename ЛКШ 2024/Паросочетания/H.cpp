#include<bits/stdc++.h>

using namespace std;

const int MAX = 1000 + 5;
vector<vector<int>> g(MAX);
vector<int> used(MAX), now_pair(MAX, -1);
int timer = 1;

bool try_kuhn(int v) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1) {
            now_pair[to] = v;
            return 1;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}

signed main() {
    int n;
    cin >> n;
    vector<int> w(n);
    vector<pair<int, int>> to_start;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        to_start.push_back({w[i], i});
    }
    sort(to_start.rbegin(), to_start.rend());
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            cin >> v;
            v--;
            g[i].push_back(v);
        }
    }
    for (auto [wg, v] : to_start) {
        if (try_kuhn(v)) {
            timer++;
        }
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        if (now_pair[i] == -1) continue;
        ans[now_pair[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
