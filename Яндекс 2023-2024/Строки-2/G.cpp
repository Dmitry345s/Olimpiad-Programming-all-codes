#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int MAXM = 2500;
int mp[MAXM * MAXM * 6][2];

void add(int sum, int mod) {
    int i = (sum % mod + mod) % mod;
    while (mp[i][0] != sum && !(mp[i][0] == 0 && mp[i][1] == 0)) {
        ++i;
        if (i >= mod) {
            i -= mod;
        }
    }
    if (mp[i][0] == sum) {
        mp[i][1] += 1;
    } else {
        mp[i][0] = sum;
        mp[i][1] = 1;
    }
}

int mfind(int sum, int mod) {
    int i = (sum % mod + mod) % mod;
    while (mp[i][0] != sum && !(mp[i][0] == 0 && mp[i][1] == 0)) {
        ++i;
        if (i >= mod) {
            i-= mod;
        }
    }
    return mp[i][1];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    int mod = MAXM * MAXM * 6;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = a[i] + b[j];
            add(sum, mod);
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = -(c[i] + d[j]);
            ans += mfind(sum, mod);
        }
    }
    cout << ans << endl;
    return 0;
}
