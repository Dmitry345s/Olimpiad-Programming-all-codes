#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    //k = sqrt(n);
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    int m;
    cin >> m;
    vector<array<int, 3>> c(m);
    for (int i = 0; i < m; ++i) {
        cin >> c[i][0] >> c[i][1];
        --c[i][0]; --c[i][1];
        c[i][2] = i;
    }
    sort(c.begin(), c.end());
    int MAX = 3e5 + 1;
    int k = 1300;
    int l = 0, r = 0;
    int ans = 0;
    vector<int> cnt(MAX);
    vector<int> rans(m);
    int u = 0;
    for (int i = 0; i < (n + k - 1) / k; ++i) {
        vector<array<int, 3>> now;
        while (u < m && c[u][0] < min((i + 1) * k, n)) {
            now.push_back({c[u][1], c[u][0], c[u][2]});
            u++;
        }
        sort(now.begin(), now.end());
        for (int j = 0; j < (int)now.size(); ++j) {
            int nl = now[j][1], nr = now[j][0];
            while (r <= nr) {
                cnt[a[r]]++;
                if (cnt[a[r]] == 1) {
                    ans++;
                }
                ++r;
            }
            while (l > nl) {
                l--;
                cnt[a[l]]++;
                if (cnt[a[l]] == 1) {
                    ans++;
                }
            }
            while (l < nl) {
                cnt[a[l]]--;
                if (cnt[a[l]] == 0) {
                    ans--;
                }
                l++;
            }
            rans[now[j][2]] = ans;
        }
        while (r < min((i + 1) * k, n)) {
            cnt[a[r]]++;
            if (cnt[a[r]] == 1) {
                ans++;
            }
            ++r;
        }
        while (r > min((i + 1) * k, n)) {
            r--;
            cnt[a[r]]--;
            if (cnt[a[r]] == 0) {
                ans--;
            }
        }
        while (l < min((i + 1) * k, n)) {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0) {
                ans--;
            }
            l++;
        }
    }
    for (int i = 0; i < m; ++i) {
        cout << rans[i] << '\n';
    }
    return 0;
}
