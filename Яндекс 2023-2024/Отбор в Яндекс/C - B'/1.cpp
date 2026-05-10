#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> c(n + 1);
    for (int i = 0; i < n; ++i) {
        int hh, mm;
        char _;
        cin >> hh >> _ >> mm;
        c[i] = hh * 60 + mm;
    }
    c.back() = 23 * 60 + 59;
    double ans = 100;
    for (int i = 1; i < c.size(); ++i) {
        int time = c[i] - c[i - 1];
        if (i & 1) {
            double d = (double) time / a;
            d = min((double) 1, d);
            ans -= d * 100;
            ans = max(ans, (double) 0);
        } else {
            double d = (double) time / b;
            d = min((double) 1, d);
            ans += d * 100;
            ans = min((double) 100, ans);
        }
    }
    cout << setprecision(7) << ans << endl;
    return 0;
}
