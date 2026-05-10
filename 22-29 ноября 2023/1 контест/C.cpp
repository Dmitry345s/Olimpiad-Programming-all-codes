#include<bits/stdc++.h>

#define int long long

using namespace std;

vector<int> c(2001);

int f(int st, int a, int b, int now, int n) {
    if (a <= now && now <= b && st == n) {
        return 0;
    }
    if (now > b) {
        return 2e9;
    }
    if (st == n) {
        return 2e9;
    }
    int ans = 2e9;
    int sum = 0;
    for (int i = st; i < n; ++i) {
        sum += c[i];
        ans = min(ans, sum | f(i + 1, a, b, now + 1, n));
    }
    return ans;
}

signed main() {
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    //cout << f(0, a, b, 0, n) << endl;
    if (n <= 23) {
        int rans = 2e9;
        for (int mask = 0; mask < (1 << n); ++mask) {
            int ans = 0;
            int lsum = 0;
            int cnt = 0;
            int last = 0;
            for (int bit = 0; bit < n; ++bit) {
                lsum += c[bit];
                if ((mask >> bit) & 1) {
                    ans |= lsum;
                    lsum = 0;
                    last = bit;
                    cnt++;
                }
            }
            if (last != n - 1) {
                ans |= lsum;
                cnt++;
            }
            if (a <= cnt && cnt <= b) {
                rans = min(ans, rans);
            }
        }
        cout << rans << endl;
        return 0;
    }
    if (n <= 39) {
        cout << f(0, a, b, 0, n) << endl;
        return 0;
    }
    int rans = 0;
    for (int i = 0; i < n; ++i) {
        rans = (rans | c[i]);
    }
    if (a <= 2 && b >= 2) {
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += c[j];
            }
            int sum2 = 0;
            for (int j = i; j < n; ++j) {
                sum2 += c[j];
            }
            rans = min(rans, (sum | sum2));
        }
    }
    if (a == 1) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += c[i];
        }
        rans = min(rans, sum);
    }
    cout << rans << endl;
    /*int nrans = 0;
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + c[i - 1];
        nrans = max(nrans, c[i - 1]);
    }
    cout << 0 << endl;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (b + 1, vector<int> (n + 1, 0)));
    vector<vector<int>> dp2(n + 1, vector<int> (b + 1, 2e9));
    for (int i = 0; i <= b; ++i) {
        dp2[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= b; ++j) {
            for (int l = 1; l <= i; ++l) {
                cout << i << " " << j << " " << l << " ";
                dp[i][j][l] = dp2[i - l][j - 1] | (pref[i] - pref[i - l]);
                cout << dp[i][j][l] << endl;
                dp2[i][j] = min(dp2[i][j], dp[i][j][l]);
            }
        }
    }
    int rans = 2e9;
    for (int i = a; i <= b; ++i) {
        rans = min(rans, dp2.back()[i]);
    }
    cout << rans << endl;*/
    return 0;
}
