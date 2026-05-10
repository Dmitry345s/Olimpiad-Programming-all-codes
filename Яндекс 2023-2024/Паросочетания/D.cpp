#include<bits/stdc++.h>

using namespace std;

int MAX = 500 + 1;
vector<vector<int>> g(MAX);
vector<int> used(MAX), pr(MAX, -1);

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    int m;
    cin >> m;
    vector<array<int, 5>> a(m);
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        a[i][0] = (s[0] - '0') * 10 * 60 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
        cin >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
    }
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            int ans1 = abs(a[i][1] - a[i][3]) + abs(a[i][2] - a[i][4]);
            if (a[i][0] + ans1 + abs(a[i][3] - a[j][1]) + abs(a[i][4] - a[j][2]) + 1 <= a[j][0]) {
                g[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        used.assign(m, 0);
        try_kuhn(i);
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (pr[i] == -1) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
