#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, a;
    cin >> n >> a;
    vector<pair<int, int>> now;
    now.push_back({a, 0});
    now.push_back({a, 0});
    n -= 2 * a;
    if (n < 0) {
        cout << -1 << endl;
        return 0;
    }
    if (n % 2) {
        if (a == 2) {
            cout << -1 << endl;
            return 0;
        }
        now[0].second += 1;
        n -= 1;
    }
    if (n < a) {
        cout << -1 << endl;
        return 0;
    }
    int na = n - a;
    if (na < a - 1) {
        now.push_back({a, na});
    } else {
        n /= 2;
        now.push_back({n + 1, n - 1});
    }
    for (auto [u, v] : now) {
        cout << u << " " << v << endl;
    }
    return 0;
}
