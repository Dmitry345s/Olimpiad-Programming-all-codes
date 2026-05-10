#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e2 + 1, INF = 3 * MAX + 1;

int f[MAX][MAX];

signed main() {
    for (int i = 0; i < MAX; ++i) {
        f[i][i] = INF;
        f[i][0] = INF;
        f[0][i] = INF;
    }
    for (int i = 1; i < MAX; ++i) {
        for (int j = 1; j < MAX; ++j) {
            if (i == j) continue;
            vector<int> all(INF + 1, 0);
            for (int u = 0; u < i; ++u) {
                all[f[u][j]]++;
            }
            for (int u = 0; u < j; ++u) {
                all[f[i][u]]++;
            }
            for (int u = 0; u < min(i, j); ++u) {
                all[f[i - u - 1][j - u - 1]]++;
            }
            for (int u = 0; u < INF + 1; ++u) {
                if (all[u] == 0) {
                    f[i][j] = u;
                    break;
                }
            }
        }
    }
    //cout << f[1][2] << endl;
    int n;
    cin >> n;
    int ans = 0;
    int fl1 = 0, fl2 = 0;
    for (int i = 0; i < n; ++i) {
        int l, c;
        cin >> l >> c;
        ans ^= f[l][c];
        if (l == 0 && c == 0) fl1 = 1;
        if (l == 0 && c != 0 || l != 0 && c == 0) {
            fl2 = 1;
        }
    }
    //cout << ans << endl;
    if (fl1 == 1) {
        cout << "N" << endl;
        return 0;
    }
    if (fl2 == 1) {
        cout << "Y" << endl;
        return 0;
    }
    if (ans == 0) {
        cout << "N" << endl;
    } else {
        cout << "Y" << endl;
    }
    return 0;
}
