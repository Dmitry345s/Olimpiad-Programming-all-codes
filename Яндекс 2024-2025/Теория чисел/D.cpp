#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e6 + 2, MOD = 1e9 + 7;
int cnt[MAX], uf[MAX];

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> prec(n + 1);
    int now = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        prec[i + 1] = (now * (i + 1)) % MOD;
        now = (now * 2) % MOD;
    }
    int ans = 0;
    for (int i = MAX - 1; i >= 2; --i) {
        int in = 0;
        int to_get = 0;
        for (int j = i; j < MAX; j += i) {
            in = (in + uf[j]) % MOD;
            to_get += cnt[j];
        }
        int in2 = (prec[to_get] - in + MOD) % MOD;
        uf[i] = in2;
        ans = (ans + (i * in2) % MOD) % MOD;
    }
    cout << ans << endl;
}
