#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    vector<int> pows(17);
    pows[0] = 1;
    for (int i = 1; i < 17; ++i) {
        pows[i] = pows[i - 1] * 3;
    }
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int in, x, y;
            cin >> in >> x >> y;
            a[in] = x;
            b[in] = y;
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            vector<int> to_ans;
            vector<pair<int, int>> to_ans2;
            for (int j = l; j <= r; ++j) {
                if (a[j] * 2 <= b[j]) {
                    to_ans.push_back(a[j]);
                    to_ans.push_back(b[j] - a[j]);
                } else {
                    to_ans2.push_back({b[j], a[j]});
                }
            }
            sort(to_ans.begin(), to_ans.end());
            sort(to_ans2.begin(), to_ans2.end());
            vector<int> pref((int)to_ans.size() + 1);
            for (int j = 1; j < (int)pref.size(); ++j) {
                pref[j] = pref[j - 1] + to_ans[j - 1];
            }
            vector<int> pref2((int)to_ans2.size() + 1);
            vector<int> pref3((int)to_ans2.size() + 1);
            vector<int> suf((int)to_ans2.size() + 1, INF);
            vector<int> to_get(2 * (int)to_ans2.size() + 1);
            for (int j = 1; j < (int)pref2.size(); ++j) {
                pref2[j] = pref2[j - 1] + to_ans2[j - 1].first;
                pref3[j] = min(pref3[j - 1], to_ans2[j - 1].second - to_ans2[j - 1].first);
            }
            for (int j = (int)to_ans2.size() - 1; j >= 0; --j) {
                suf[j] = min(suf[j + 1], to_ans2[j].second);
            }
            if (1 < (int)to_get.size()) {
                to_get[1] = suf[0];
            }
            for (int j = 0; j < (int)to_ans2.size(); ++j) {
                int x = (j + 1) * 2;
                to_get[x] = pref2[j + 1];
                int x2 = x + 1;
                if (x2 >= (int)to_get.size()) continue;
                //cout << j << " " << x << " " << x2 << endl;
                int u = pref2[j + 1] + suf[j + 1];
                int u2 = INF;
                if (j < (int)to_ans2.size() - 1) {
                    u2 = pref2[j + 1] + pref3[j + 1] + to_ans2[j + 1].first;
                }
                to_get[x2] = min(u, u2);
            }
            int ans = INF;
            for (int u = 0; u < min(k + 1, (int)to_get.size()); u += 2) {
                int tt = k - u;
                if (tt < (int)pref.size()) {
                    ans = min(ans, to_get[u] + pref[tt]);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
