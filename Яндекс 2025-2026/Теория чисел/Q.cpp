#include<bits/stdc++.h>

# define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> all;
    int x = m;
    for (int i = 2; i * i <= m; ++i) {
        if (x % i == 0) {
            all.push_back(i);
        }
        while (x % i == 0) {
            x /= i;
        }
    }
    if (x != 1) {
        all.push_back(x);
    }
    int ans = 0;
    int tt = (int)all.size();
    for (int mask = 0; mask < (1 << tt); ++mask) {
        int now = 1;
        int cnt = 0;
        for (int j = 0; j < tt; ++j) {
            if ((mask >> j) & 1) {
                now *= all[j];
                cnt++;
            }
        }
        if (cnt % 2) {
            ans -= n / now;
        } else {
            ans += n / now;
        }
    }
    cout << ans << endl;
    return 0;
}
