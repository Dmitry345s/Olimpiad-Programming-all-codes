#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    multiset<int> c;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sum += x;
        c.insert(x);
    }
    vector<pair<int, int>> sale(m);
    for (int i = 0; i < m; ++i) {
        cin >> sale[i].second;
    }
    for (int i = 0; i < m; ++i) {
        cin >> sale[i].first;
    }
    sort(sale.rbegin(), sale.rend());
    for (int i = 0; i < m; ++i) {
        auto it = c.lower_bound(sale[i].second);
        if (it != c.end()) {
            sum -= sale[i].first;
            c.erase(it);
        }
    }
    cout << sum << endl;
    return 0;
}
