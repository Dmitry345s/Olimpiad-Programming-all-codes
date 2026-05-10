#include<bits/stdc++.h>

#define int long long
using ull = unsigned long long;

using namespace std;

const ull P = 179;

ull fpow(ull p, int x) {
    ull ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans *= p;
        }
        x /= 2;
        p *= p;
    }
    return ans;
}

signed main() {
    int m;
    cin >> m;
    if (m == 1) {
        cout << 2 << endl;
        return 0;
    }
    int n = (1 << m);
    vector<int> a(n);
    vector<int> f(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        f[a[i]] = i;
    }
    vector<int> lens(n);
    for (int i = 0; i < n; ++i) {
        lens[i] = f[a[i] ^ (n - 1)];
        //cout << lens[i] << " ";
    }
    //cout << endl;
    int now = 0;
    int cnt = 0;
    vector<int> g;
    vector<ull> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i];
        if (lens[i] > i) {
            now++;
            pref[i + 1] ^= fpow(P, i);
        } else {
            now--;
            pref[i + 1] ^= fpow(P, lens[i]);
        }
        //cout << pref[i + 1] << endl;
    }
    vector<int> pref2(n + 1);
    map<pair<int, ull>, int> mp;
    mp[{0, 0}] = 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        pref2[i + 1] = (pref2[i] ^ a[i]);
        ans += mp[{pref2[i + 1], pref[i + 1]}];
        mp[{pref2[i + 1], pref[i + 1]}]++;
    }
    //cout << endl;
    //cout << ans << endl;
    //cout << n * (n + 1) / 2 << endl;
    cout << n * (n + 1) / 2 - ans << endl;
    return 0;
}
