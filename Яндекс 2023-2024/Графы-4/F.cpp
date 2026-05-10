#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int MAX = 2e5, ln = 25;
vector<int> pows(ln), prp(MAX);
vector<vector<int>> sparse(ln, vector<int> (MAX, 1e9));

void build(vector<ll> & a, int n) {
    for (int i = 0; i < ln; ++i) {
        pows[i] = (1 << i);
    }
    prp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        prp[i] = prp[i / 2] + 1;
    }
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = a[i];
    }
    for (int i = 1; i < ln; ++i) {
        for (int j = 0; j < n; ++j) {
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][min(j + pows[i - 1], n - 1)]);
        }
    }
}

ll get(int l, int r) {
    int sz = r - l + 1;
    return min(sparse[prp[sz]][l], sparse[prp[sz]][r - pows[prp[sz]] + 1]);
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    cin >> a[0];
    for (int i = 1; i < n; ++i) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
        //cout << a[i] << " ";
    }
    //cout << endl;
    build(a, n);
    ll v, u;
    cin >> u >> v;
    ll lans = 0;
    lans = get(min(v, u) - 1, max(v, u) - 1);
    for (int i = 1; i < m; ++i) {
        //cout << u << " " << v << " " << lans << endl;
        u = (17 * u + 751 + lans + 2 * i) % n + 1;
        v = (13 * v + 593 + lans + 5 * i) % n + 1;
        lans = get(min(u, v) - 1, max(u, v) - 1);
    }
    cout << u << " " << v << " " << lans << endl;
    return 0;
}
