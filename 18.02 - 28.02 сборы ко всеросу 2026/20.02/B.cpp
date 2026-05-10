#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, c;
    cin >> n >> c;
    int yy = 3 * c;
    vector<int> all;
    for (int i = 1; i <= n; ++i) {
        int l = -c - 1, r = c + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            cout << "? " << -yy << " " << m << " " << yy << " " << m << endl;
            int up, dw;
            cin >> up >> dw;
            if (n - up >= i) {
                r = m;
            } else {
                l = m;
            }
        }
        all.push_back(r);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    vector<pair<int, int>> ans;
    int nowup = n;
    for (int now : all) {
        cout << "? " << -yy << " " << now << " " << yy << " " << now << endl;
        int up, dw;
        cin >> up >> dw;
        int cnt = n - up - dw;
        nowup -= cnt;
        for (int i = 0; i < cnt; ++i) {
            int l = -c - 1, r = c + 1;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                cout << "? " << m - yy << " " << now - 1 << " " << m << " " << now << endl;
                int up, dw;
                cin >> up >> dw;
                up -= nowup;
                if (up >= i) {
                    r = m;
                } else {
                    l = m;
                }
            }
            ans.push_back({l, now});
        }
    }
    cout << "Ready!" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
