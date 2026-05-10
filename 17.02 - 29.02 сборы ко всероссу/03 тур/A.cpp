#include<bits/stdc++.h>

#define int long long

using namespace std;

mt19937_64 rnd(time(0));

int mod = 1791791791;
int p = 57;

int pow(int a, int x) {
    if (x == 0) return 1ll;
    int k = pow(a, x / 2);
    //cout << a << " " << x << " " << k << endl;
    if (x % 2 == 1) {
        return (a * ((k * k) % mod)) % mod;
    }
    return (k * k) % mod;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> pref(n + 1);
    pref[0] = 0;
    vector<int> h(n + 1);
    h[0] = 0;
    set<array<int, 3>> st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
        h[i + 1] = (h[i] + pow(p, a[i])) % mod;
        st.insert({pow(p, a[i]), i, a[i]});
        //cout << pow(p, a[i]) << endl;
    }
    //cout << 0 << endl;
    for (int i = 0; i < q; ++i) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        --l1; --l2;
        int ch = pref[r1] - pref[l1] - (pref[r2] - pref[l2]);
        //cout << ch << endl;
        if (ch == 0) {
            cout << "NO" << endl;
            continue;
        }
        int ch2 = ((h[r1] - h[l1] + mod) % mod - (h[r2] - h[l2] + mod) % mod + mod) % mod;
        //cout << ch2 << endl;
        int ch4 = pow(p, abs(ch)) - 1;
        if (ch < 0) {
            ch4 = mod - ch4;
        }
        int ch3 = (ch2 * pow(ch4, mod - 2)) % mod;
        //cout << (long long)ch3 << endl;
        if (ch < 0) {
            swap(l1, l2);
            swap(r1, r2);
        }
        auto it = st.upper_bound(array<int, 3>{ch3, l2, -1});
        //cout << 0 << endl;
        if (it == st.end() || (*it)[0] != ch3 || (*it)[1] > r2) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
