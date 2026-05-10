#include<bits/stdc++.h>

#define int long long

using namespace std;

int dp[2][2][2];

signed main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += (x[i] - x[j]) * (y[i] + y[j]);
    }
    if (sum % 2) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int s = ((x[i] - x[i - 1]) * (y[i] + y[i - 1]) % 2 + 2) % 2;
        if (s) {
            for (int i1 = 0; i1 < 2; ++i1) {
                for (int j1 = 0; j1 < 2; ++j1) {
                    swap(dp[i1][j1][0], dp[i1][j1][1]);
                }
            }
        }
        int x1 = (x[i] % 2 + 2) % 2, y1 = (y[i] % 2 + 2) % 2;
        ans += dp[x1][y1 ^ 1][0] + dp[x1 ^ 1][y1][0] + dp[x1][y1][0] + dp[x1 ^ 1][y1 ^ 1][1];
        int x2 = (x[i - 1] % 2 + 2) % 2, y2 = (y[i - 1] % 2 + 2) % 2;
        dp[x2][y2][s] += 1;
    }
    cout << ans - 1 << endl;
    return 0;
}

/*
reverse(s.begin(), s.end());
    for (int k = 0; k < 100; ++k) {
        for (int i = 0; i < n - 1; ++i) {
            if (s.back() == 'M') {
                a[i] = max(a[i], a[i + 1]);
            } else {
                a[i] = min(a[i], a[i + 1]);
            }
        }
        s.pop_back();
        n--;
    }
    reverse(s.begin(), s.end());
*/
