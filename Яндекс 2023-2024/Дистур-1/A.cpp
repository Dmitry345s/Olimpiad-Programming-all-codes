#include<bits/stdc++.h>

#define int long long

using namespace std;

int get(int len, int f) {
    int st = max((long long) 0, f - len + 1);
    len = f - st + 1;
    return st * len + len * (len - 1) / 2;
}
bool check(int m, int n, int x, int c) {
    int cnt = n / (m + 1);
    int ans = get(cnt, c) * (m + 1) + (n % (m + 1)) * max((long long) 0, c - cnt);
    return ans >= x;
}

signed main() {
    int n, x, c;
    cin >> n >> x >> c;
    int l = -1, r = 1e18;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(m, n, x, c)) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == 1e18) {
        cout << -1 << endl;
    } else {
        cout << r << endl;
    }
    return 0;
}
