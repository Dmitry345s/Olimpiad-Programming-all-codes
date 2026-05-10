#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops","O3")

//#define int long long

using namespace std;
const int C = 100, MAX = 5e4;

int ts[C][MAX];
int cnt[C];
int nows[MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<string> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i];
    }
    vector<int> now(k);
    for (int i = 0; i < k; ++i) {
        now[i] = i;
    }
    vector<pair<int, int>> ans(n, {-1, -1});
    for (int mask = 0; mask < (1 << k); ++mask) {
        now.clear();
        for (int b = 0; b < k; ++b) {
            if ((mask >> b) & 1) {
                now.push_back(b);
            }
        }
        for (int b = 0; b < k; ++b) {
            if (!((mask >> b) & 1)) {
                now.push_back(b);
            }
        }
        for (int i = 0; i < n; ++i) {
            nows[i] = i;
        }
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < n; ++j) {
                int tt = (int)all[nows[j]][now[k - i - 1]] - 33;
                ts[tt][cnt[tt]] = nows[j];
                cnt[tt]++;
            }
            int t = 0;
            for (int j = 0; j < C; ++j) {
                for (int y = 0; y < cnt[j]; ++y) {
                    nows[t] = ts[j][y];
                    t++;
                }
                cnt[j] = 0;
            }
        }
        for (int i = 1; i < n; ++i) {
            int u = 0;
            while (u < k && all[nows[i]][now[u]] == all[nows[i - 1]][now[u]]) {
                u++;
            }
            ans[nows[i - 1]] = max(ans[nows[i - 1]], pair<int, int>{u, nows[i]});
            ans[nows[i]] = max(ans[nows[i]], pair<int, int>{u, nows[i - 1]});
        }
    }
    for (auto [mx, in] : ans) {
        cout << k - mx << " " << in + 1 << endl;
    }
    return 0;
}
