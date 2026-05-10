#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, r, c;
    cin >> r >> c >> n;
    vector<pair<int, int>> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i].first >> cs[i].second;
    }
    if (n == 1) {
        int x = max(cs[0].first - 1 + cs[0].second - 1, r - cs[0].first + c - cs[0].second);
        int y = max(r - cs[0].first + cs[0].second - 1, cs[0].first - 1 + c - cs[0].second);
        cout << max(x, y) << endl;
    }
    return 0;
}
