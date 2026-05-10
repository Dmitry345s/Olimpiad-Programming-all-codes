#include<bits/stdc++.h>

using namespace std;

set<vector<int>> st;

void solve(vector<int> all, int cnt, int n) {
    if (cnt == n) {
        int fl = 1;
        for (int j = 1; j < n; ++j) {
            if (abs(all[j] - all[j - 1]) < n / 2) {
                fl = 0;
                break;
            }
        }
        if (fl) st.insert(all);
        return;
    }
    vector<int> used(n);
    for (int i = 0; i < cnt; ++i) {
        used[all[i]] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i] && abs(all[cnt - 1] - i) >= n / 2) {
            all[cnt] = i;
            solve(all, cnt + 1, n);
            all[cnt] = -1;
        }
    }

}

signed main() {
    int _, n;
    cin >> _ >> n;
    if (n <= 15 && n % 2 == 1) {
        vector<int> all(n);
        for (int i = 0; i < n; ++i) {
            all[i] = -1;
        }
        for (int i = 0; i < n; ++i) {
            all[0] = i;
            solve(all, 1, n);
            all[0] = -1;
        }
    }
    while (_--) {
        int k;
        cin >> k;
        vector<int> msk(n, -1);
        for (int i = 0; i < k; ++i) {
            int a, b;
            cin >> a >> b;
            msk[a] = b;
        }
        if (n % 2 == 0) {
            vector<int> ans1(n), ans2(n);
            for (int i = 0; i < n; i += 2) {
                ans1[i] = i / 2 + n / 2;
            }
            for (int i = 1; i < n; i += 2) {
                ans1[i] = i / 2;
            }
            ans2 = ans1;
            reverse(ans2.begin(), ans2.end());
            int ans = 0;
            int fl = 1;
            for (int j = 0; j < n; ++j) {
                if (msk[j] != -1 && msk[j] != ans1[j]) {
                    fl = 0;
                }
                if (j >= 1 && abs(ans1[j] - ans1[j - 1]) < n / 2) {
                    fl = 0;
                }
            }
            ans += fl;
            fl = 1;
            for (int j = 0; j < n; ++j) {
                if (msk[j] != -1 && msk[j] != ans2[j]) {
                    fl = 0;
                }
                if (j >= 1 && abs(ans2[j] - ans2[j - 1]) < n / 2) {
                    fl = 0;
                }
            }
            ans += fl;
            cout << ans << endl;
            continue;
        }
        int ans = 0;
        for (auto all : st) {
            int fl = 1;
            for (int j = 0; j < n; ++j) {
                if (msk[j] != -1 && msk[j] != all[j]) {
                    fl = 0;
                    break;
                }
            }
            ans += fl;
        }
        cout << ans << endl;
    }
    return 0;
}
