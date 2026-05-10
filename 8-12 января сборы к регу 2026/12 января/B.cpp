#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            f[i][j] = (c == '#');
        }
    }
    int ans = 0;
    for (int u = 0; u < n; ++u) {
        vector<int> now(m);
        for (int d = u; d < n; ++d) {
            for (int j = 0; j < m; ++j) {
                now[j] += f[d][j];
            }
            int len = d - u + 1;
            int mlen = (s + len - 1) / len;
            int r = 0;
            int cnt = 0;
            for (int l = 0; l < m; ++l) {
                while (r < m && r - l < mlen) {
                    cnt += now[r];
                    r++;
                }
                if (r - l < mlen) break;
                int ch = 0;
                while (r < m && cnt <= k) {
                    cnt += now[r];
                    r++;
                    ch++;
                }
                if (ch && cnt > k) {
                    --r;
                    cnt -= now[r];
                }
                //cout << u << " " << d << " " << r << " " << l << " " << cnt << endl;
                ans += r - l - mlen + (cnt <= k);
                cnt -= now[l];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
