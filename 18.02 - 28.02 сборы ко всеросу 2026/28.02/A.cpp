#include<bits/stdc++.h>

using namespace std;

const int MOD = 46337;

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> cnt(k);
    int rcnt = 0;
    int r = 0;
    int len = n;
    for (int l = 0; l < n; ++l) {
        while (r < n && rcnt < k) {
            cnt[a[r]]++;
            if (cnt[a[r]] == 1) rcnt++;
            r++;
        }
        if (rcnt == k) {
            if (r - l < len) {
                len = r - l;
            }
        }
        cnt[a[l]]--;
        if (cnt[a[l]] == 0) rcnt--;
    }
    //cout << len << endl;
    cnt.assign(k, 0);
    rcnt = 0;
    int ans = 0;
    r = 0;
    int now = 1;
    for (int l = 0; l < n; ++l) {
        while (r < n && rcnt < k) {
            if (cnt[a[r]] != 0) {
                now = (now * fpow(cnt[a[r]], MOD - 2)) % MOD;
            }
            cnt[a[r]]++;
            now = (now * cnt[a[r]]) % MOD;
            if (cnt[a[r]] == 1) rcnt++;
            r++;
        }
        //cout << l << " " << r << " " << len << endl;
        if (rcnt == k && r - l == len) {
            ans = (ans + now) % MOD;
        }
        now = (now * fpow(cnt[a[l]], MOD - 2)) % MOD;
        cnt[a[l]]--;
        if (cnt[a[l]] == 0) {
            rcnt--;
        } else {
            now = (now * cnt[a[l]]) % MOD;
        }
    }
    cout << ans << endl;
}
