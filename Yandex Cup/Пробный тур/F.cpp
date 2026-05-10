#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<pair<int, int>>> all(n);
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> now;
        now.push_back({a[i], i});
        int u = a[i];
        for (int j = i - 1; j >= 0; --j) {
            u &= a[j];
            if (u != now.back().first) {
                now.push_back({u, j});
            }
        }
        all[i] = now;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        vector<int> to_ans;
        for (int j = l; j < r; ++j) {
            for (auto [t, in] : all[j]) {
                if (l <= in) {
                    to_ans.push_back(t);
                }
            }
        }
        sort(to_ans.begin(), to_ans.end());
        to_ans.erase(unique(to_ans.begin(), to_ans.end()), to_ans.end());
        int now = 0;
        for (int j = 0; j < (int)to_ans.size(); ++j) {
            if (to_ans[j] != now) {
                break;
            }
            now++;
        }
        cout << now << '\n';
    }
    return 0;
}
