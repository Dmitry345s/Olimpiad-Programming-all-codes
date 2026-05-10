#include<bits/stdc++.h>

#define int long long

using namespace std;

int solve(vector<int> p, int n) {
    multiset<int> all;
    for (int i = 0; i < n; ++i) all.insert(p[i]);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int v = *all.begin();
        all.erase(all.begin());
        ans += abs(v - i);
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i] >> c[i];
        --r[i]; --c[i];
    }
    cout << solve(r, n) + solve(c, n) << endl;
    return 0;
}
