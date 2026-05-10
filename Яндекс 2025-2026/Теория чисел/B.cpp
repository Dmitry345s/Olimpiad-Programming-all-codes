#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e7 + 1;
int sieve[MAX], sieve2[MAX];

void solve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (sieve[i]) continue;
        for (int j = i * i; j < MAX; j += i) {
            sieve[j] = 1;
        }
        int k = (i - n * n % i) % i;
        //cout << k << " " << i << endl;
        for (int j = k; j < MAX; j += i) {
            sieve2[j] = 1;
        }
    }
}

signed main() {
    int n;
    cin >> n;
    solve(n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += (sieve2[i] == 0);
    }
    cout << ans << endl;
    return 0;
}
