#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int ts, tf, t;
    cin >> ts >> tf >> t;
    int n;
    cin >> n;
    if (n == 0) {
        cout << ts << endl;
        return 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int free = ts;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        free = max(free, a[i]) + t;
        b[i] = free;
    }
    int st = 0;
    if (a[0] >= 1) {
        st = min(a[0] - 1, ts);
    }
    int minm = ts - st;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] == a[i + 1] || a[i + 1] == 0) continue;
        if (b[i] < a[i + 1] && b[i] <= tf - t) {
            st = b[i];
        } else {
            if (b[i] - (a[i + 1] - 1) < minm && b[i] <= tf - t) {
                st = a[i + 1] - 1;
                minm = b[i] - (a[i + 1] - 1);
            }
        }
    }
    if (b[n - 1] <= tf - t) {
        st = b[n - 1];
    }
    cout << st << endl;
    return 0;
}
