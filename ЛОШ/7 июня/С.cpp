#include<iostream>
#include<vector>
#include<set>

using namespace std;

long long mod = 1e9 + 7;

long long pow(long long a, long long x) {
    if (x == 0) {
        return 1;
    }
    long long p = pow(a, x / 2);
    if (x % 2 == 1) {
        return (((p * p) % mod) * a) % mod;
    }
    return (p * p) % mod;
}

int main() {
    int n, k;
    long long t;
    cin >> n >> t >> k;
    if (n == k) {
        long long ans = pow(n, t);
        ans = pow(ans, 1e9 + 5);
        cout << ans << endl;
    } else {
        cout << -5 << endl;
    }
    return 0;
}
