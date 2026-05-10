#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 21, A = 10;

int get(string a, int k) {
    if (a == "0") return 0;
    int dp[MAX][A][MAX][2][2];
    for (int i = 0; i < MAX; ++i) {
        for (int c = 0; c < A; ++c) {
            for (int j = 0; j < MAX; ++j) {
                for (int u1 = 0; u1 < 2; ++u1) {
                    for (int u2 = 0; u2 < 2; ++u2) {
                        dp[i][c][j][u1][u2] = 0;
                    }
                }
            }
        }
    }
    dp[1][0][0][0][0] = 1;
    for (int i = 1; i < a[0] - '0'; ++i) {
        dp[1][i][1][0][(k == 1)] = 1;
    }
    //cout << a[0] - '0' << endl;
    dp[1][a[0] - '0'][1][1][(k == 1)] = 1;
    for (int i = 1; i < (int)a.size(); ++i) {
        for (int c = 0; c < A; ++c) {
            for (int j = 0; j < MAX; ++j) {
                for (int c2 = 0; c2 < A; ++c2) {
                    int x = j * (c == c2) + (c2 != 0 || j != 0);
                    if (x >= MAX) continue;
                    //cout << c << " " << c2 << " " << j << " " << x << " " << dp[i][j][c][0][1] + dp[i][j][c][1][1] << endl;
                    dp[i + 1][c2][x][0][(x >= k)] += dp[i][c][j][0][0];
                    dp[i + 1][c2][x][0][1] += dp[i][c][j][0][1];
                    if (c2 < a[i] - '0') {
                        dp[i + 1][c2][x][0][(x >= k)] += dp[i][c][j][1][0];
                        dp[i + 1][c2][x][0][1] += dp[i][c][j][1][1];
                    } else if (c2 == a[i] - '0') {
                        dp[i + 1][c2][x][1][(x >= k)] += dp[i][c][j][1][0];
                        dp[i + 1][c2][x][1][1] += dp[i][c][j][1][1];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < A; ++i) {
        for (int j = 1; j < MAX; ++j) {
            //cout << i << " " << j << " " << dp[(int)a.size()][i][j][0][1] << " " << dp[(int)a.size()][i][j][1][1] << endl;
            ans += dp[(int)a.size()][i][j][0][1] + dp[(int)a.size()][i][j][1][1];
        }
    }
    return ans;
}

signed main() {
    int a, b;
    int k;
    cin >> a >> b >> k;
    //cout << get(to_string(b), k) << endl;
    cout << get(to_string(b), k) - get(to_string(a - 1), k) << endl;
    return 0;
}
