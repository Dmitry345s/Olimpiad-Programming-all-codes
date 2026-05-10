#include<bits/stdc++.h>

#define int long long

using namespace std;

int get(vector<pair<int, int>> b, int x) {
    int u = lower_bound(b.begin(), b.end(), pair<int, int>{x, -1e9}) - b.begin() - 1;
    int ret = 0;
    int sz = 0;
    if (u != -1) {
        ret = b[u].second;
        sz = b[u].first;
    }
    int sz2 = x - sz - 1;
    ret += ((sz2 + 1) * sz2) / 2;
    return ret;
}

signed main() {
    int l, r;
    cin >> l >> r;
    int cnt = 0;
    vector<pair<int, int>> a;
    while (cnt < 1e12) {
        cnt += a.size() + 1;
        int k = 0;
        if (a.size() > 0) {
            k = a.back().second;
        }
        pair<int, int> ha = {cnt, k + ((a.size() + 1) * (a.size() + 2)) / 2};
        a.push_back(ha);
    }
    int ans1 = get(a, l), ans2 = get(a, r + 1);
    cout << ans2 - ans1 << endl;
    return 0;
}
