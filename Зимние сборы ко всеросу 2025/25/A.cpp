#include<bits/stdc++.h>

//#define int long long

using namespace std;

const long long MAX = 300;
char ch[MAX][MAX][MAX];
long long cnt[MAX][MAX][MAX];
int a[MAX][MAX];
char f[MAX][MAX];

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cnt[i][j][j] = a[i][j];
            ch[i][j][j] = f[i][j];
            for (int j2 = j + 1; j2 < m; ++j2) {
                if (f[i][j2] == f[i][j2 - 1] || ch[i][j][j2 - 1] == -1) {
                    ch[i][j][j2] = -1;
                } else {
                    ch[i][j][j2] = ch[i][j][j];
                }
                cnt[i][j][j2] = cnt[i][j][j2 - 1] + a[i][j2];
            }
        }
    }
    long long maxm = -2e18;
    array<int, 4> ans = {-1, -1, -1, -1};
    for (int j = 0; j < m; ++j) {
        for (int j2 = j; j2 < m; ++j2) {
            long long minm = 0;
            int in = 0;
            long long mx = 0;
            pair<int, int> in2;
            long long x = 0;
            for (int i = 0; i < n; ++i) {
                if (ch[i][j][j2] == -1) {
                    minm = 2e18;
                    in = -1;
                } else if (i > 0 && ch[i][j][j2] == ch[i - 1][j][j2]) {
                    minm = x;
                    in = i;
                }
                x += cnt[i][j][j2];
                if (mx < x - minm) {
                    in2 = {in, i};
                    mx = x - minm;
                }
                if (x < minm) {
                    minm = x;
                    in = i + 1;
                }
            }
            if (mx > maxm) {
                maxm = mx;
                ans = {in2.first, j, in2.second, j2};
            }
        }
    }
    cout << ans[0] << " " << ans[1] << endl << ans[2] << " " << ans[3] << endl;
    return 0;
}
