#include<bits/stdc++.h>

using namespace std;

const int INF = 15;

int ans = INF;

void solve(int n, vector<int> & a, vector<int> now, int sum) {
    if ((int)now.size() == n) {
        int g = 0;
        for (int i = 0; i < n; ++i) {
            g = __gcd(g, now[i] + a[i]);
        }
        if (g == 1) ans = min(ans, sum);
        return;
    }
    for (int i = 0; i < INF - sum; ++i) {
        now.push_back(i);
        solve(n, a, now, sum + i);
        now.pop_back();
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int gg = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        gg = __gcd(gg, a[i]);
    }
    if (n <= 15) {
        solve(n, a, {}, 0);
        cout << ans << endl;
    } else {
        if (gg == 1) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }
}
