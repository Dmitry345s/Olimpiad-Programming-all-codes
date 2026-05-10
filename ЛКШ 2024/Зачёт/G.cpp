#include<bits/stdc++.h>

using namespace std;

signed main() {
    long long n;
    cin >> n;
    long long ans = 0;
    vector<long long> to_get;
    for (long long i = 1; (i * i) <= n; ++i) {
        if (i * i == n) {
            ans += i;
        } else {
            ans += n / i;
            to_get.push_back(n / i);
        }
        //cout << i << endl;
    }
    for (int i = 0; i < (int)to_get.size() - 1; ++i) {
        //cout << to_get[i] << " ";
        ans += (to_get[i] - to_get[i + 1]) * (i + 1);
    }
    if (to_get.back() > (long long)sqrtl(n)) {
        ans += n / to_get.back();
    }
    cout << ans << endl;
    return 0;
}
