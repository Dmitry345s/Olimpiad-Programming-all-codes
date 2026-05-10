#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e9;

signed main() {
    int r, c;
    cin >> r >> c;
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
        --all[i].first; --all[i].second;
    }
    int ans = INF;
    for (int len1 = 0; len1 <= r; ++len1) {
        for (int len2 = 0; len2 <= r; ++len2) {
            vector<vector<int>> to_ans(r);
            for (auto [x, y] : all) {
                for (int u = 0; u <= len1; ++u) {
                    if (x - u >= 0) {
                        to_ans[x - u].push_back(y);
                    }
                }
                for (int u = 0; u <= len2; ++u) {
                    if (x + u < r) {
                        to_ans[x + u].push_back(y);
                    }
                }
            }
            int t1 = 0, t2 = 0;
            int sumtt = 0;
            for (int i = 0; i < r; ++i) {
                sort(to_ans[i].begin(), to_ans[i].end());
                to_ans[i].erase(unique(to_ans[i].begin(), to_ans[i].end()), to_ans[i].end());
                if (to_ans[i].empty()) {
                    sumtt = INF;
                    break;
                }
                t1 = max(t1, to_ans[i][0]);
                t2 = max(t2, c - 1 - to_ans[i].back());
                for (int u = 0; u < (int)to_ans[i].size() - 1; ++u) {
                    sumtt = max(sumtt, to_ans[i][u + 1] - to_ans[i][u] - 1);
                }
            }
            //cout << len1 << " " << len2 << " " << t1 << " " << t2 << " " << sumtt << endl;
            ans = min(ans, len1 + len2 + max(sumtt, t1 + t2));
        }
    }
    cout << ans << endl;
    return 0;
}
