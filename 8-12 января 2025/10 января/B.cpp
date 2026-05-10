#include<bits/stdc++.h>
#pragma GCC optimize("fast-math","O3","unroll-loops")

using namespace std;
using ll = long long;

int is_pr(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return 0;
    }
    return 1;
}

const ll INF = 1e18;
const int MAX = 100;
ll e[MAX];

int ch(int & pr, ll & e, ll n) {
    ll k = n;
    ll now = pr;
    while (n / now >= pr) {
        k += n / now;
        if (k >= e) return 1;
        now *= pr;
    }
    k += n / now;
    return k >= e;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    vector<int> pr;
    int x = 2;
    while ((int)pr.size() < 101) {
        if (is_pr(x)) {
            pr.push_back(x);
        }
        x++;
    }
    while (_--) {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> e[i];
        }
        ll ans = 1;
        for (int i = 0; i < m; ++i) {
            if (e[i] == 0) continue;
            ll l = 0, r = e[i];
            while (l + 1 < r) {
                ll n = (l + r) / 2;
                if (ch(pr[i], e[i], n)) {
                    r = n;
                } else {
                    l = n;
                }
                if (r * pr[i] < ans) break;
            }
            ans = max(ans, r * pr[i]);
            if (ans == INF) break;
        }
        cout << ans << '\n';
    }
    return 0;
}
