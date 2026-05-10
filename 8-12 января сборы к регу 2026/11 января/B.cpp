#include<bits/stdc++.h>

#define int long long

using namespace std;

vector<array<int, 3>> solve(vector<array<int, 3>> now, int mxx, int t) {
     vector<int> allins;
     vector<pair<int, int>> alltps;
     for (auto [x, tp, in] : now) {
        allins.push_back(in);
        if (tp == 0) {
            int st = mxx - x;
            if (st > t) {
                alltps.push_back({x + t, -tp});
            } else {
                int nt = t - st;
                int u = nt / mxx;
                int u2 = nt % mxx;
                int en = 0;
                int ntp = 0;
                if (u % 2 == 0) {
                    en = mxx;
                    ntp = 1;
                }
                en += u2 * (-1 + 2 * (ntp == 0));
                alltps.push_back({en, -ntp});
            }
        } else {
            int st = x;
            if (st > t) {
                alltps.push_back({x - t, -tp});
            } else {
                int nt = t - st;
                int u = nt / mxx;
                int u2 = nt % mxx;
                int en = 0;
                int ntp = 0;
                if (u % 2 == 1) {
                    en = mxx;
                    ntp = 1;
                }
                en += u2 * (-1 + 2 * (ntp == 0));
                alltps.push_back({en, -ntp});
            }
        }
     }
     sort(alltps.begin(), alltps.end());
     vector<array<int, 3>> ans;
     for (int i = 0; i < (int)allins.size(); ++i) {
        //cout << alltps[i].second << endl;
        ans.push_back({alltps[i].first, -alltps[i].second, allins[i]});
     }
     return ans;
 }

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int w, h, k, t;
    cin >> w >> h >> k >> t;
    vector<vector<array<int, 3>>> all(h);
    vector<vector<array<int, 3>>> all2(w);
    for (int i = 0; i < k; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
        if (d % 2) {
            all[y].push_back({x, d / 2, i});
        } else {
            all2[x].push_back({y, d / 2 - 1, i});
        }
    }
    vector<array<int, 3>> ans(k);
    for (int i = 1; i < h; ++i) {
        sort(all[i].begin(), all[i].end());
        vector<array<int, 3>> now = solve(all[i], w, t);
        for (auto [x, tp, in] : now) {
            ans[in] = {x, i, tp * 2 + 1};
        }
    }
    for (int i = 1; i < w; ++i) {
        sort(all2[i].begin(), all2[i].end());
        vector<array<int, 3>> now = solve(all2[i], h, t);
        for (auto [y, tp, in] : now) {
            ans[in] = {i, y, (tp + 1) * 2};
        }
    }
    for (int i = 0; i < k; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
    }
    return 0;
}

