#include<bits/stdc++.h>

using namespace std;
using ll = long long;

ll get(ll x) {
    if (x == 1) {
        return 1;
    }
    for (ll i = 60; i >= 0; --i) {
        if (x == (1ll << i) - 1) {
            return 0;
        }
        if ((x >> i) & 1ll) {
            int ch = (x - (1ll << i) + 1) % 2;
            return (get((1ll << i) - 1) ^ get((x ^ (1ll << i))) ^ ch * (1ll << i));
        }
    }
    return 0;
}

signed main() {
    int n;
    cin >> n;
    ll ans = 0;
    vector<ll> ls(n), rs(n);
    for (int i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        ans ^= (get(r) ^ get(l) ^ l);
        ls[i] = l;
        rs[i] = r;
    }
    if (ans == 0) {
        cout << "Lose" << endl;
        return 0;
    }
    ll mx = 0;
    for (int i = 60; i >= 0; --i) {
        if ((ans >> i) & 1ll) {
            mx = i;
            break;
        }
    }
    ll st = 0;
    for (int i = 0; i < n; ++i) {
        if ((ls[i] >> mx) & 1ll) {
            st = ls[i];
            break;
        } else {
            ll ch = ((ls[i] >> mx) ^ 1);
            if ((ch << mx) <= rs[i]) {
                st = (ch << mx);
                break;
            }
        }
    }
    cout << "Win" << endl;
    cout << st << " " << (st ^ ans) << endl;
    return 0;
}
