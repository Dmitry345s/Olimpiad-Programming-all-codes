#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, c, k;
    cin >> n >> m >> c >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    n = (int)a.size();
    for (int i = n - 1; i >= 0; --i) {

    }
    return 0;
}
