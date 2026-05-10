#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> tans(n);
    vector<int> tf(n);
    for (int i = 0; i < n; ++i) {
        tans[i] = i;
        tf[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        swap(tans[tf[x]], tans[tf[y]]);
        swap(tf[x], tf[y]);
    }
    for (int i = 0; i < n; ++i) {
        cout << tans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
