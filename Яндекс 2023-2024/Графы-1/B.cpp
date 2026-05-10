#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> g;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g.push_back({a, b});
    }
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        --a;
        x[a] = i;
    }
    bool flag = true;
    for (auto[v, to] : g) {
        if (x[v] > x[to]) {
            flag = false;
        }
    }
    if (flag) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
