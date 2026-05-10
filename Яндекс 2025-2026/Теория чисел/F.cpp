#include<bits/stdc++.h>

//# define int long long

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1e6 + 1;

long long cntst[MAX], cntnw[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (1ll * ans * a) % MOD;
        }
        a = (1ll * a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //prec();
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cntst[a[i]]++;
    }
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; j += i) {
            cntnw[i] += cntst[j];
        }
    }
    for (int i = 1; i < MAX; ++i) {
        cntnw[i] = (1ll * fpow(2, cntnw[i] - 1) * cntnw[i]) % MOD;
    }
    for (int i = MAX - 1; i >= 2; --i) {
        for (int j = 2 * i; j < MAX; j += i) {
            cntnw[i] = (cntnw[i] - cntnw[j] + MOD) % MOD;
        }
    }
    long long ans = 0;
    for (int i = 2; i < MAX; ++i) {
        ans += (1ll * i * (cntnw[i])) % MOD;
    }
    cout << ans % MOD << endl;
    return 0;
}
