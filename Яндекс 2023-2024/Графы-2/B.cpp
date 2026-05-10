#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i].first >> cs[i].second;
    }
    vector<double> d(n, 1e9);
    vector<int> used(n);
    int lastmn = 0;
    d[0] = 0;
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        used[lastmn] = 1;
        ans += d[lastmn];
        double nowmn = 1e9, nlastmn = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                double x = cs[j].first - cs[lastmn].first, y = cs[j].second - cs[lastmn].second;
                d[j] = min(d[j], sqrt(x * x + y * y));
                if (nowmn > d[j]) {
                    nlastmn = j;
                    nowmn = d[j];
                }
            }
        }
        lastmn = nlastmn;
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}
