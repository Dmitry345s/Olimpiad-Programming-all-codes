#include<bits/stdc++.h>

#pragma GCC optmize("O3","unroll-loops")

//#define int long long

using namespace std;

const int INF = 1e9, MAXM = 505001;
int bag[MAXM];
int bag2[MAXM];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, l;
    cin >> m >> l;
    vector<int> all(2 * m + 1);
    vector<int> a(2 * m + 1);
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i < 2 * m + 1; ++i) {
        cin >> all[i];
        if (i > m) {
            cnt1 += all[i] * (i - m);
        }
        if (i < m) {
            cnt2 += all[i] * (m - i);
        }
    }
    if (l > cnt1 || l < -cnt2) {
        cout << "impossible" << endl;
        return 0;
    }
    fill(bag, bag + MAXM, -INF);
    bag[0] = 0;
    for (int i = m + 1; i < 2 * m + 1; ++i) {
        for (int t = 0; t < all[i]; ++t) {
            for (int j = min(cnt2 + l, cnt1); j >= i - m + 100 * (i - m); --j) {
                bag[j] = max(bag[j], bag[j - i + m] + 1);
            }
        }
    }
    fill(bag2, bag2 + MAXM, -INF);
    bag2[0] = 0;
    for (int i = 0; i < m; ++i) {
        for (int t = 0; t < all[i]; ++t) {
            for (int j = min(cnt1 - l, cnt2); j >= m - i + 100 * (i + 1); --j) {
                bag2[j] = max(bag2[j], bag2[j - m + i] + 1);
            }
        }
    }
    int ans = -INF;
    for (int i = 0; i < MAXM; ++i) {
        int y = (-1) * (l - i);
        if (y >= 0 && y < MAXM) {
            ans = max(ans, bag[i] + bag2[y]);
        }
    }
    if (ans < 0) {
        cout << "impossible" << endl;
        return 0;
    }
    cout << ans + all[m] << endl;
}
