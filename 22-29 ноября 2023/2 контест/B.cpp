#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> b(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        b[a[i].second] = a[i].first;
    }
    int ans = 5 * n;
    for (int i = 3; i < min(n + 1, 1ll * 200); ++i) {
        for (int j = 2; j < i; ++j) {
            for (int l = 1; l < j; ++l) {
                if (b[i] + b[j] > b[l] && b[j] + b[l] > b[i] && b[i] + b[l] > b[j]) {
                    ans = min(ans, i + j + l);
                }
            }
        }
    }
    if (ans == 5 * n) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
