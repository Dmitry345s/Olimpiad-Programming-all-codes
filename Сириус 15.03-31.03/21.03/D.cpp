#include<bits/stdc++.h>

#define int long long

using namespace std;

int tr(vector<int> a, int x) {
    int maxm = 0, minm = 1e9;
    int n = a.size();
    int l = 0;
    int ans = 0;
    while (l < n) {
        maxm = 0;
        minm = 1e9;
        while (l < n && maxm - minm <= x) {
            maxm = max(maxm, a[l]);
            minm = min(minm, a[l]);
            l++;
        }
        if (maxm - minm > x) {
            ans += 1;
            --l;
        }
    }
    return ans;
}

signed main() {
    int n, w, q;
    cin >> n >> w >> q;
    vector<int> x(n);
    int maxm = 0, minm = 1e9;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    minm = x[0];
    maxm = x[0];
    int cnt = 0;
    for (int i = 1; i < n; ++i) {
        if (x[i] < minm) {
            cnt++;
            minm = x[i];
        }
        if (x[i] > maxm) {
            cnt++;
            maxm = x[i];
        }
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << (cnt + w - k - 1) / (w - k) - 1 << endl;
    }
}
