#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int g;
    cin >> g;
    int k, n, s, t;
    cin >> k >> n >> s >> t;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    if (g == 1) {
        vector<int> ch;
        for (int i = 0; i < n; ++i) {
            ch.push_back(x[i] * x[i] + y[i] * y[i]);
        }
        sort(ch.begin(), ch.end());
        cout << setprecision(20) << sqrtl(ch[k - 1]) * t << endl;
    }
    return 0;
}
