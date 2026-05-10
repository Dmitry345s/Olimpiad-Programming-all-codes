#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(k);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> b[i];
    }
    if (k == 1) {
        for (int i = 0; i < n; ++i) {
            cout << i + 1 << endl;
        }
        return 0;
    }
    vector<int> s;
    for (int i = 0; i < k - 1; ++i) {
        s.push_back(b[i + 1] - b[i]);
    }
    s.push_back(2e9);
    for (int i = 0; i < n - 1; ++i) {
        s.push_back(a[i + 1] - a[i]);
    }
    vector<int> z(s.size());
    z[0] = s.size();
    int l = 0, r = 1;
    for (int i = 1; i < s.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < s.size() && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
        if (i >= k && z[i] == k - 1) {
            cout << i - k + 1 << " ";
        }
    }
    return 0;
}
