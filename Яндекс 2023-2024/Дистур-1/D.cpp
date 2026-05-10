#include<bits/stdc++.h>

#define int long long

using namespace std;

int get (int x) {
    int now = x;
    int cnt = 0;
    int i = 2;
    while (i * i <= now) {
        while (now % i == 0) {
            now /= i;
            cnt++;
        }
        i++;
    }
    if (now != 1) {
        cnt++;
    }
    return cnt;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        int ans = 0;
        int minm = 1e18;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int x = gcd(a[i], a[j]);
            int mminm = get(a[i] / x) + get(a[j] / x);
            if (mminm < minm) {
                minm = mminm;
                ans = j + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
