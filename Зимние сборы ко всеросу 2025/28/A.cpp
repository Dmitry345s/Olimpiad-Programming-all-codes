#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector<int> pref(n);
    int now = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            pref[i] = a[i];
        } else {
            int x = max(0ll, a[i] - (now + pref[i - 1]));
            pref[i] = pref[i - 1] + x;
        }
        now += b[i];
        //cout << pref[i] << " ";
    }
    //cout << endl;
    vector<int> suf(n);
    vector<int> sufsm(n);
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            suf[i] = a[i];
            sufsm[i] = b[i];
        } else {
            int u = max(a[i], max(0ll, suf[i + 1] - b[i]));
            suf[i] = u;
            sufsm[i] = sufsm[i + 1] + b[i];
        }
        //cout << suf[i] << " ";
    }
    //cout << endl;
    int ans = suf[0];
    for (int i = 1; i < n; ++i) {
        int st = suf[i];
        int st2 = st + sufsm[i];
        int u = st + max(0ll, pref[i] - st2);
        ans = min(ans, u);
    }
    cout << ans << endl;
    return 0;
}
