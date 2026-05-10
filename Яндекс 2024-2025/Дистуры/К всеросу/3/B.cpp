#include<bits/stdc++.h>

using namespace std;

const int INF = 500;

signed main() {
    int r, s;
    cin >> r >> s;
    vector<vector<char>> f(r, vector<char> (s));
    vector<vector<int>> a(r, vector<int> (s, -1));
    vector<vector<vector<int>>> dp(r, vector<vector<int>> (s, vector<int> (r + 1, -INF)));
    vector<vector<vector<int>>> p(r, vector<vector<int>> (s, vector<int> (r + 1, INF)));
    int t = -1;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            cin >> f[i][j];
            if (f[i][j] == 'M') {
                dp[i][j][0] = 0;
                t = j;
            }
            if (f[i][j] == '.') {
                a[i][j] = 1;
            }
            if (f[i][j] == ')') {
                a[i][j] = 0;
            }
            if (f[i][j] == '(') {
                a[i][j] = 2;
            }
            if (f[i][j] == '*') {
                a[i][j] = 3;
            }
        }
    }
    for (int i = r - 2; i >= 0; --i) {
        for (int j = 0; j < s; ++j) {
            for (int b = 0; b <= r; ++b) {
                int x = -1;
                for (int u = -1; u <= 1; ++u) {
                    if (j + u < 0 || s <= j + u) continue;
                    if (a[i][j] == 1 && dp[i + 1][j + u][b] >= 0) {
                        if (dp[i + 1][j + u][b] > dp[i][j][b]) {
                            p[i][j][b] = u;
                            dp[i][j][b] = dp[i + 1][j + u][b];
                        } else if (dp[i + 1][j + u][b] == dp[i][j][b]) {
                            if (p[i][j][b] == INF || a[i + 1][j + p[i][j][b]] > a[i + 1][j + u]) {
                               p[i][j][b] = u;
                            }
                        }
                    }
                    if (a[i][j] == 0 && b < r && dp[i + 1][j + u][b + 1] >= 0) {
                        if (dp[i + 1][j + u][b + 1] + 1 > dp[i][j][b]) {
                            p[i][j][b] = u;
                            dp[i][j][b] = dp[i + 1][j + u][b + 1] + 1;
                        } else if (dp[i + 1][j + u][b + 1] + 1 == dp[i][j][b]) {
                            if (p[i][j][b] == INF || a[i + 1][j + p[i][j][b]] > a[i + 1][j + u]) {
                               p[i][j][b] = u;
                            }
                        }
                    }
                    if (a[i][j] == 2 && 0 < b && dp[i + 1][j + u][b - 1] >= 0) {
                        if (dp[i + 1][j + u][b - 1] + 1 > dp[i][j][b]) {
                            p[i][j][b] = u;
                            dp[i][j][b] = dp[i + 1][j + u][b - 1] + 1;
                        } else if (dp[i + 1][j + u][b - 1] + 1 == dp[i][j][b]) {
                            if (p[i][j][b] == INF || a[i + 1][j + p[i][j][b]] > a[i + 1][j + u]) {
                               p[i][j][b] = u;
                            }
                        }
                    }
                    if (a[i][j] == 3) {
                        dp[i][j][b] = -INF;
                        if (dp[i + 1][j + u][b] > x) {
                            p[i][j][b] = u;
                            x = dp[i + 1][j + u][b];
                        } else if (dp[i + 1][j + u][b] == x) {
                            if (p[i][j][b] == INF || a[i + 1][j + p[i][j][b]] > a[i + 1][j + u]) {
                               p[i][j][b] = u;
                            }
                        }
                    }
                }
                //`cout << i << " " << j << " " << b << " " << dp[i][j][b] << " " << p[i][j][b] << endl;
            }
        }
    }
    string ans = "";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (a[i][j] == 3) {
                int b = 0;
                string now;
                int x = i, y = j;
                while (p[x][y][b] != INF) {
                    int c = a[x][y];
                    y += p[x][y][b];
                    x += 1;
                    if (c == 0) {
                        b += 1;
                    } else if (c == 2) {
                        b -= 1;
                    }
                    if (f[x][y] == '(' || f[x][y] == ')') {
                        now.push_back(f[x][y]);
                    }
                }
                if (x != r - 1 || y != t) continue;
                reverse(now.begin(), now.end());
                if ((int)now.size() > (int)ans.size()) {
                    ans = now;
                } else if ((int)now.size() == (int)ans.size()) {
                    ans = min(ans, now);
                }
            } else if (i == 0) {
                int b = 0;
                string now;
                int x = i, y = j;
                if (p[x][y][b] == INF || dp[x][y][b] < 0) continue;
                if (f[x][y] == '(' || f[x][y] == ')') {
                    now.push_back(f[x][y]);
                }
                while (p[x][y][b] != INF) {
                    int c = a[x][y];
                    y += p[x][y][b];
                    x += 1;
                    if (c == 0) {
                        b += 1;
                    } else if (c == 2) {
                        b -= 1;
                    }
                    if (f[x][y] == '(' || f[x][y] == ')') {
                        now.push_back(f[x][y]);
                    }
                }
                if (x != r - 1 || y != t) continue;
                reverse(now.begin(), now.end());
                if ((int)now.size() > (int)ans.size()) {
                    ans = now;
                } else if ((int)now.size() == (int)ans.size()) {
                    ans = min(ans, now);
                }
            }
        }
    }
    cout << (int)ans.size() << endl;
    cout << ans << endl;
    return 0;
}
