#include<bits/stdc++.h>

using namespace std;

signed main () {
    int n;
    cin >> n;
    vector<vector<char>> a(6, vector<char> (n));
    vector<vector<array<int, 10>>> b(n + 1, vector<array<int, 10>> (6));
    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[0][i] >> a[1][i] >> a[2][i] >> a[3][i] >> a[4][i] >> a[5][i];
        for (int j = 0; j < 6; ++j) {
            for (int l = a[j][i] - '0' + 1; l < 10; ++l) {
                cnt += b[i][j][l];
            }
        }
        b[i + 1] = b[i];
        for (int j = 0; j < 6; ++j) {
            b[i + 1][j][a[j][i] - '0'] += 1;
        }
    }
    vector<array<int, 2>> c(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int l = 0; l < a[j][i] - '0'; ++l) {
                c[i][1] += b.back()[j][l];
            }
            for (int l = a[j][i] - '0' + 1; l < 10; ++l) {
                c[i][0] += b.back()[j][l];
            }
        }
    }
    long long ans = cnt;
    for (int i = n - 1; i > 0; --i) {
        cnt = cnt - c[i][0] + c[i][1];
        ans = min(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
