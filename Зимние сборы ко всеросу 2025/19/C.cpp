#include<bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

const int MAX = 15e2 * 15e2 + 1, MAX2 = 15e2 + 1;

int cnt[MAX];
int pref[MAX2];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> f2(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            f2[i][j] = c - '0';
        }
    }
    vector<vector<int>> f(m, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = f2[j][i];
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        fill(pref, pref + n + 1, 0);
        for (int j = i; j < m; ++j) {
            int sum = 0;
            cnt[0]++;
            for (int k = 0; k < n; ++k) {
                sum += f[j][k];
                pref[k + 1] += sum;
                if (pref[k + 1] - q >= 0) {
                    ans += cnt[pref[k + 1] - q];
                }
                cnt[pref[k + 1]]++;
            }
            for (int k = 0; k <= n; ++k) {
                cnt[pref[k]]--;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
