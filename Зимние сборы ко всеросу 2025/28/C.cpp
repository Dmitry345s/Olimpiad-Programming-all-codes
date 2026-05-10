#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e18;

signed main() {
    int p, b, d, n;
    cin >> b >> p >> d >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> cnt(p);
    a.push_back(b);
    for (int i = 0; i < n; ++i) {
        cnt[a[i] % p]++;
    }
    int ans = INF;
    for (int i = 0; i < p; ++i) {
        ans = min(ans, i + b + ((i + b - 1) / p - cnt[(p - i) % p]) * d);
    }
    cout << ans << endl;
    return 0;
    /*a.insert(a.begin(), 0);
    map<int, int> now;
    now[0] = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        int y = a[i] - a[i - 1];
        map<int, int> rnow;
        rnow[y % p] = INF;
        for (auto [j, x] : now) {
            int del = ((j + y - 1) / p) * d + y;
            rnow[(j + y) % p] = x + del;
            int del2 = ((y - 1) / p) * d + (p - j) + y;
            rnow[y % p] = min(rnow[y % p], x + del2);
        }
        swap(now, rnow);
    }
    int ans = INF;
    for (auto [j, x] : now) {
        ans = min(ans, x);
    }
    cout << ans << endl;
    return 0;*/
}
