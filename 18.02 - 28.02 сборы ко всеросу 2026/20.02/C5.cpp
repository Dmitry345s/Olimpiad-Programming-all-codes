#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 3e5 + 1;

int fpow(int a, int x) {
    int ans = 1;
    while(x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}
 int f[MAX];
 int rf[MAX];

 int c(int k, int n) {
     return f[n] * rf[n - k] % MOD * rf[k] % MOD;
 }

signed main() {
    f[0] = 1;
    rf[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        f[i] = (f[i - 1] * i) % MOD;
        rf[i] = (rf[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    int n;
    cin >> n;
    n *= 2;
    string s;
    cin >> s;
    int bl = 0;
    vector<int> len(n + 1);
    int ls = -1;
    int cntall = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            bl++;
        } else {
            bl--;
        }
        if (bl == 0) {
            len[i - ls]++;
            ls = i;
            cntall++;
        }
    }
    int ans = 1;
    int now = cntall;
    for (int i = 0; i <= n; ++i) {
        //cout << i << " " << len[i] << " " << now << endl;
        //cout << c(len[i], now) << endl;
        ans = (ans * c(len[i], now)) % MOD;
        now -= len[i];
    }
    cout << ans << endl;
    return 0;
}
