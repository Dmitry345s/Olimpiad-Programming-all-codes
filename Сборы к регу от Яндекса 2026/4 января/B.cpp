#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 3e6;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n, k;
        cin >> n >> k;
        vector<array<int, 3>> all(n);
        int mx = 0;
        int tt = 0;
        for (int i = 0; i < n; ++i) {
            cin >> all[i][0] >> all[i][1] >> all[i][2];
            if (all[i][0] > mx) {
                mx = all[i][0];
                tt = all[i][2];
            }
        }
        int l = tt - 1, r = INF;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            array<vector<pair<int, int>>, 2> now;
            now[0].clear();
            now[1].clear();
            for (int i = 0; i < n; ++i) {
                if (all[i][1] <= m) {
                    now[0].push_back({all[i][0], i});
                }
                if (all[i][2] <= m) {
                    now[1].push_back({all[i][0], i});
                }
            }
            sort(now[0].begin(), now[0].end());
            sort(now[1].rbegin(), now[1].rend());
            vector<int> ch(n);
            array<int, 2> in = {0, 0};
            int tr = 1;
            int nsum = 0;
            int msum = 0;
            while (in[tr] < (int)now[tr].size()) {
                while (in[tr] < (int)now[tr].size() && ch[now[tr][in[tr]].second]) {
                    in[tr]++;
                }
                //cout << tr << " " << in[tr] << endl;
                if (in[tr] < (int)now[tr].size()) {
                    //cout << now[tr][in[tr]].first << " " << now[tr][in[tr]].second << endl;
                    ch[now[tr][in[tr]].second] = 1;
                    nsum += now[tr][in[tr]].first * (tr + (tr == 0) * -1);
                    //cout << nsum << endl;
                    msum = max(nsum, msum);
                    tr ^= 1;
                }
            }
            if (msum >= k) {
                r = m;
            } else {
                l = m;
            }
        }
        cout << r << endl;
    }
    return 0;
}
