#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5;
vector<int> g[MAX];

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        a[u]++;
        a[v]++;
    }
    int fl = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2) {
            fl = 0;
        }
    }
    if (fl) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
