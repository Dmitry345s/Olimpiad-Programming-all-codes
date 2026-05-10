#include<bits/stdc++.h>

#define int long long

using namespace std;

bool check(__int128 x, vector<int> & b, int cnt) {
    for (int i = 0; i < (int)b.size(); ++i) {
        int y = (x + b[i] - 1) / b[i];
        cnt -= y;
    }
    return cnt >= 0;
}

bool check2(__int128 x, vector<int> & a, vector<int> & b, __int128 cnt) {
    __int128 m = cnt / (int)a.size();
    for (int i = 0; i < (int)a.size(); ++i) {
        __int128 nx = x;
        if (a[i] > b[i]) {
            __int128 y = min(m, (x + a[i] - 1) / a[i]);
            cnt -= y;
            nx -= y * a[i];
            nx = max(nx, (__int128)0);
        }
        __int128 y = (nx + b[i] - 1) / b[i];
        cnt -= y;
    }
    return cnt >= 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    if (m == 1) {
        int ans = 2e9;
        for (int i = 0; i < n; ++i) {
            ans = min(max(a[i], b[i]), ans);
        }
        cout << ans << endl;
        return 0;
    }
    __int128 l = 0, r = 1e9 * 1e9 * 1e3;
    while (l + 1 < r) {
        __int128 c = (l + r) / 2;
        if (check2(c, a, b, n * m)) {
            l = c;
        } else {
            r = c;
        }
    }
    vector<int> ans;
    while (l != 0) {
        ans.push_back((int)(l % 10));
        l /= 10;
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i];
    }
}
