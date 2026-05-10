#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e6 + 1;
int cnt[MAX];

int solve(int n, int t, vector<int> r, vector<int> c, vector<int> v) {
    vector<array<int, 3>> all;
    for (int i = 0; i < t; ++i) {
        all.push_back({v[i], r[i], c[i]});
    }
    sort(all.begin(), all.end());
    int ans = 0;
    int l = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        int now = 0;
        while (l < t && all[l][0] < i) {
            int can = all[l][1] + all[l][2] - all[l][0];
            if (can >= 0) {
                cnt[can]++;
            }
            l++;
        }
        for (int j = 0; j < MAX; j += i) {
            now += cnt[j];
        }
        ans = max(ans, now);
    }
    return t - ans;
}


/*signed main() {
    int n, t;
    cin >> n >> t;
    vector<int> r(t), c(t), v(t);
    for (int i = 0; i < t; ++i) {
        cin >> r[i];
    }
    for (int i = 0; i < t; ++i) {
        cin >>   c[i];
    }
    for (int i = 0; i < t; ++i) {
        cin >> v[i];
    }
    cout << solve(n, t, r, c, v) << endl;
}   */
