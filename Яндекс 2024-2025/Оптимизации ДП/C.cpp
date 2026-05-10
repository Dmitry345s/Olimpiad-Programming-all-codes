#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 5e4 + 2, MAX2 = 102;
int x[MAX];
int pref1[MAX], pref2[MAX];
long double dp[MAX][MAX2];
const long double INF = 1e18;

void solve(int l, int r, int c, int optl, int optr) {
    if (l == r) return;
    int m = (l + r) / 2;
    int last = -1;
    dp[m][c] = INF;
    for (int i = optl; i <= min(m, optr - 1); ++i) {
        long double b = pref2[m + 1] - pref2[i];
        long double a = (m - i + 1);
        long double c2 = pref1[m + 1] - pref1[i];
        long double x = 0;
        if (i != 0) {
            x = dp[i - 1][c - 1];
        }
        long double now = (-b * b) / (4 * a) + c2 + x;
        //cout << m << " " << i << " " << now << endl;
        if (now < dp[m][c]) {
            dp[m][c] = now;
            last = i;
        }
    }
    solve(l, m, c, optl, last + 1);
    solve(m + 1, r, c, last, optr);
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(x, x + n);
    for (int i = 0; i < n; ++i) {
        pref1[i + 1] = pref1[i] + x[i] * x[i];
        pref2[i + 1] = pref2[i] + 2 * x[i];
    }
    for (int i = 0; i < n; ++i) {
        long double b = pref2[i + 1] - pref2[0];
        long double a = i + 1;
        long double c = pref1[i + 1] - pref1[0];
        //cout << a << " " << b << " " << c << endl;
        dp[i][0] = (-b * b) / (4 * a) + c;
        //cout << dp[i][0] << endl;
    }
    for (int i = 1; i < k; ++i) {
        solve(0, n, i, 0, n);
    }
    cout << setprecision(20) << dp[n - 1][k - 1] << endl;
    return 0;
}
