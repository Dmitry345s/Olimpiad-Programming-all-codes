#include<bits/stdc++.h>

using namespace std;

const int MAX = 250000, MAX2 = 1e4;
bitset<MAX> ans;
int all[MAX][4], f[MAX2], now[MAX];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < n; ++i) cin >> all[i][0] >> all[i][1] >> all[i][2] >> all[i][3];
    for (int i = 0; i < t; ++i) cin >> f[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            now[i] = now[i] - (f[j] <= all[i][0]) * all[i][2] + (!(f[j] <= all[i][0])) * all[i][1];
            now[i] *= (now[i] >= 0);
            ans[i] = (ans[i] | (now[i] >= all[i][3]));
        }
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
}
