#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, t;
    cin >> n >> t;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<array<int, 3>> all(t);
    for (int i = 0; i < t; ++i) {
        cin >> all[i][0] >> all[i][1];
        all[i][2] = i;
        all[i][0]--; all[i][1]--;
    }
    int k = 450;
    sort(all.begin(), all.end());
    vector<vector<array<int, 3>>> bl(1);
    int now = 0;
    for (int i = 0; i < t; ++i) {
        if (all[i][0] >= (now + 1) * k) {
            now++;
            bl.push_back({});
        }
        bl[now].push_back({all[i][1], all[i][0], all[i][2]});
    }
    long long ans = 0;
    int MAX = 1e6 + 3;
    vector<long long> cnt(MAX);
    vector<long long> rans(t);
    int l = 0, r = 0;
    for (int i = 0; i < (int)bl.size(); ++i) {
        sort(bl[i].begin(), bl[i].end());
        for (int j = 0; j < (int)bl[i].size(); ++j) {
            while (r <= bl[i][j][0]) {
                ans -= cnt[a[r]] * cnt[a[r]] * a[r];
                cnt[a[r]]++;
                ans += cnt[a[r]] * cnt[a[r]] * a[r];
                r++;
            }
            while (l < bl[i][j][1]) {
                ans -= cnt[a[l]] * cnt[a[l]] * a[l];
                cnt[a[l]]--;
                ans += cnt[a[l]] * cnt[a[l]] * a[l];
                l++;
            }
            while (l > bl[i][j][1]) {
                --l;
                ans -= cnt[a[l]] * cnt[a[l]] * a[l];
                cnt[a[l]]++;
                ans += cnt[a[l]] * cnt[a[l]] * a[l];
            }
            rans[bl[i][j][2]] = ans;
        }
        while (r < min((i + 1) * k, n)) {
            ans -= cnt[a[r]] * cnt[a[r]] * a[r];
            cnt[a[r]]++;
            ans += cnt[a[r]] * cnt[a[r]] * a[r];
            r++;
        }
        while (r > min((i + 1) * k, n)) {
            --r;
            ans -= cnt[a[r]] * cnt[a[r]] * a[r];
            cnt[a[r]]--;
            ans += cnt[a[r]] * cnt[a[r]] * a[r];
        }
        while (l < min((i + 1) * k, n)) {
            ans -= cnt[a[l]] * cnt[a[l]] * a[l];
            cnt[a[l]]--;
            ans += cnt[a[l]] * cnt[a[l]] * a[l];
            l++;
        }
    }
    for (int i = 0; i < t; ++i) {
        cout << rans[i] << '\n';
    }
    return 0;
}
