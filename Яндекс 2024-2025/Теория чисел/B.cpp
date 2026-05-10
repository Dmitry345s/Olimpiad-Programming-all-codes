#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e7 + 2;

int sieve[MAX], to_ans[MAX];

void solve(int n) {
    long long x = n * n;
    to_ans[0] = 1;
    for (int i = 2; i <= n; ++i) {
        if (sieve[i] == 0) {
            for (int j = i; j < MAX; j += i) {
                sieve[j] = i;
            }
            for (int j = (i - x % i); j < MAX; j += i) {
                to_ans[j] = 1;
            }
        }
    }
}

signed main() {
    int n;
    cin >> n;
    solve(n);
    int ans = n + 1;
    for (int i = 0; i <= n; ++i) {
        ans -= to_ans[i];
    }
    cout << ans << endl;
    return 0;
}
