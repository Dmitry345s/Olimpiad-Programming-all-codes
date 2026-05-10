#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> cnt(n, vector<int> (n));
    for (int _ = 0; _ < n - 1; ++_) {
        for (int v = 0; v < n; ++v) {
            int flag = 1;
            for (int u = v + 1; u < n; ++u) {
                if (cnt[u][v]) continue;
                cout << "? 1 " << v + 1 << " 1 " << u + 1 << endl;
                string tr;
                cin >> tr;
                if (tr == "YES") {
                    cnt[u][v] = 1;
                    cnt[v][u] = 1;
                    flag = 0;
                    cout << "! " << v + 1 << " " << u + 1 << endl;
                    break;
                }
            }
            if (!flag) break;
        }
    }
}
