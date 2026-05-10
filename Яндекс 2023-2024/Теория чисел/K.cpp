#include<bits/stdc++.h>

using namespace std;


signed main() {
    long long n;
    cin >> n;
    long long i = 2;
    long long now = 1;
    while (i * i * i <= n) {
        if (n % (i * i) == 0) {
            n /= i * i;
            now *= i;
        } else if (n % i == 0) {
            n /= i;
        } else {
            i++;
        }
    }
    long long x = sqrt(n);
    if (x * x == n) {
        now *= x;
    }
    cout << now / 2 + 1 << endl;
}
