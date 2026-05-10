#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i].first >> x[i].second;
    }
    sort(x.begin(), x.end());
    int r = 1e9;
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (x[i].second == 1 && x[i + 1].second == 0) {
            cnt += 1;
        }
        if (x[i].second + x[i + 1].second == 1) {
            r = min(r, abs(x[i].first - x[i + 1].first));
        }
    }
    if (x[n - 1].second == 1) {
        cnt += 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (x[i].second && x[i + 1].second) {
            if (abs(x[i].first - x[i + 1].first) >= r) {
                cnt += 1;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}
