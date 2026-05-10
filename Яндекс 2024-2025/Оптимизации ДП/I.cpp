#include<bits/stdc++.h>

# define int long long

using namespace std;

const int LEN = 1000;

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> dp(LEN, vector<int> (10));
    if (n < 10) {
        cout << n << endl;
        return 0;
    }
    for (int i = 0; i < 10; ++i) {
        dp[0][i] = 1;
    }
    dp[0][0] = 0;
    int cr = -1;
    for (int i = 1; i < LEN; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int j2 = j; j2 < 10; ++j2) {
                dp[i][j] += dp[i - 1][j2];
            }
        }
        int now = 0;
        for (int j = 0; j < 10; ++j) {
            now += dp[i][j];
            if (now >= n) {
                cr = i;
                now = -1;
                break;
            }
        }
        if (now == -1) {
            break;
        }
    }
    vector<int> to_ans;
    int st = 0;
    while (cr >= 0) {
        int now = 0;
        for (int i = st; i < 10; ++i) {
            now += dp[cr][i];
            if (now >= n) {
                now -= dp[cr][i];
                n -= now;
                st = i;
                cr--;
                to_ans.push_back(i);
                break;
            }
        }
    }
    int fl = -1;
    for (int i = 0; i < (int)to_ans.size(); ++i) {
        if (fl == -1 && to_ans[i] == 0) continue;
        cout << to_ans[i];
        fl = 0;
    }
    return 0;
}
