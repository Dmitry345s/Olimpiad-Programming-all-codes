#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        --c;
        a[c].push_back(i);
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        int mayans = 1;
        int l = 0, j = 1;
        while(j < a[i].size()) {
            if (a[i][j] - a[i][l] - 1 - (j - l - 1) <= k) {
                mayans = max(mayans, j - l + 1);
                ++j;
            } else {
                ++l;
            }
        }
        ans = max(ans, mayans);
    }
    cout << ans << endl;
    return 0;
}
