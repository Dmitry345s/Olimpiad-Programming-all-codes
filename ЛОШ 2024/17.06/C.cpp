#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int s = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s += a[i];
    }
    vector<int> pows(n + 1);
    pows[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pows[i] = pows[i - 1] * 3;
    }
    int rans = 1e9;
    for (int mask = 0; mask < pows[n - 1]; ++mask) {
        vector<int> dels(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            int y = (mask / pows[i]) % 3;
            if (y == 2) {
                dels[i] = -1;
            } else {
                dels[i] = y;
            }
        }
        int now = 0;
        int sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            now += dels[i];
            sum += now;
        }
        if ((s - sum) % n != 0) continue;
        int x = (s - sum) / n;
        now = x;
        vector<int> b = a;
        int nans = 0;
        for (int i = 0; i < n - 1; ++i) {
            b[i + 1] += b[i] - now;
            nans += abs(b[i] - now);
            b[i] = now;
            now += dels[i];
        }
        rans = min(rans, nans);
    }
    cout << rans << endl;
    return 0;
}
