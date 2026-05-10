#include<bits/stdc++.h>

using namespace std;

using ll = long long;
vector<array<ll, 3>> f, s;
int MAX = 2e5;
vector<pair<ll, ll>> tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {s[l][1], l};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

pair<ll, ll> get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return {-1, -1};
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    freopen("dowry.in", "r", stdin);
    freopen("dowry.out", "w", stdout);
    int n;
    cin >> n;
    ll l, r;
    cin >> l >> r;
    vector<ll> w(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> v[i];
    }
    for (int mask = 0; mask < (1 << (n / 2)); ++mask) {
        ll sum1 = 0, sum2 = 0;
        for (int i = 0; i < (n / 2); ++i) {
            if ((mask >> i) & 1) {
                sum1 += w[i];
                sum2 += v[i];
            }
        }
        f.push_back({sum1, sum2, mask});
    }
    for (int mask = 0; mask < (1 << ((n + 1) / 2)); ++mask) {
        int mask2 = (mask << (n / 2));
        ll sum1 = 0, sum2 = 0;
        for (int i = (n / 2); i < n; ++i) {
            if ((mask2 >> i) & 1) {
                sum1 += w[i];
                sum2 += v[i];
            }
        }
        s.push_back({sum1, sum2, mask2});
    }
    sort(s.begin(), s.end());
    for (int i = 0; i < (int)s.size(); ++i) {
        //cout << s[i][0] << " " << s[i][1] << " " << s[i][2] << endl;
    }
    build(1, 0, (int)s.size());
    ll ans = 0;
    int ansmask1 = -1, ansmask2 = -1;
    for (int i = 0; i < (int)f.size(); ++i) {
        if (f[i][0] > r) continue;
        int ql = upper_bound(s.begin(), s.end(), array<ll, 3>{l - f[i][0], -1, -1}) - s.begin();
        int qr = upper_bound(s.begin(), s.end(), array<ll, 3>{r - f[i][0], (ll)1e18, (ll)1e18}) - s.begin();
        if (ql == qr) continue;
        //cout << ql << " " << qr << endl;
        pair<ll, ll> mans = get(1, 0, (int)s.size(), ql, qr);
        if (mans.first + f[i][1] >= ans) {
            ans = mans.first + f[i][1];
            ansmask1 = f[i][2];
            ansmask2 = s[mans.second][2];
        }
    }
    //cout << ansmask1 << " " << ansmask2 << endl;
    if (ansmask1 == -1) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> rans;
    for (int i = 0; i < (n / 2); ++i) {
        if ((ansmask1 >> i) & 1) {
            rans.push_back(i + 1);
        }
    }
    for (int i = (n / 2); i < n; ++i) {
        if ((ansmask2 >> i) & 1) {
            rans.push_back(i + 1);
        }
    }
    cout << (int)rans.size() << endl;
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i] << " ";
    }
    cout << endl;
    return 0;
}
