#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (k >= n) {
        cout << n << endl;
    } else {
        cout << 2 * n - 1 << endl;
    }
    return 0;
}
