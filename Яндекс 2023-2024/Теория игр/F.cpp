#include<bits/stdc++.h>

using namespace std;

signed main() {
    int MAX = 101;
    vector<vector<int>> dp(MAX, vector<int> (MAX));
    for (int d = 1; d < 2 * MAX - 1; ++d) {
        for (int i = 0; i <= min(MAX - 1, d); ++i) {
            int j = d - i;
            if (j >= MAX) continue;
            vector<int> ch(4 * MAX);
            for (int u = 1; u <= min(i, j); ++u) {
                ch[dp[i - u][j - u]] = 1;
            }
            for (int u = 1; u <= i; ++u) {
                ch[dp[i - u][j]] = 1;
            }
            for (int u = 1; u <= j; ++u) {
                ch[dp[i][j - u]] = 1;
            }
            for (int k = 0; k < 4 * MAX; ++k) {
                if (ch[k] == 0) {
                    dp[i][j] = k;
                    break;
                }
            }
        }
    }
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int l, c;
        cin >> l >> c;
        ans ^= dp[l][c];
    }
    if (ans == 0) {
        cout << "N" << endl;
    } else {
        cout << "Y" << endl;
    }
    return 0;
}
