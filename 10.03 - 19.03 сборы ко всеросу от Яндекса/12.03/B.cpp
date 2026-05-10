#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> s(n), e(n);
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> e[i];
        all[i] = {s[i], e[i]};
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < q; ++i) {
        int st, en;
        cin >> st >> en;
        --st; --en;
        if (st == en) {
            cout << 0 << '\n';
            continue;
        }
        int now = e[st];
        int wn = e[en];
        if (s[en] <= now && now <= wn) {
            cout << 1 << '\n';
            continue;
        }
        int cnt = 0;
        int l = 0;
        int ss = -1;
        while (true) {
            while (l < n && all[l].first <= now) {
                if (all[l].second <= wn) {
                    ss = max(ss, all[l].second);
                }
                l++;
            }
            if (ss <= now) {
                cnt = -1;
                break;
            }
            now = ss;
            cnt++;
            if (s[en] <= now && now <= wn) {
                cnt++;
                break;
            }
        }
        if (cnt == -1) {
            cout << "impossible" << '\n';
            continue;
        }
        cout << cnt << '\n';
    }
    return 0;
}
