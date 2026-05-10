#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<vector<int>> all;
    int mx = 0;
    for (int i = 0; i < (1 << m); ++i) {
        vector<int> c;
        for (int j = 0; j < m; ++j) {
            if ((i >> j) & 1) {
                c.push_back(b[j]);
            }
        }
        if ((int)c.size() % 2 == 1) {
            int fl = 1;
            for (int j = 1; j < (int)c.size(); j += 2) {
                if (c[j] <= c[j - 1] || c[j] <= c[j + 1]) {
                    fl = 0;
                }
            }
            if (fl) {
                //cout << i << endl;
                all.push_back(c);
                mx = max(mx, (int)c.size());
            }
        }
    }
    sort(all.begin(), all.end());
    vector<vector<int>> tr;
    for (int i = 0; i < (1 << n); ++i) {
        vector<int> c;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                c.push_back(a[j]);
            }
        }
        if ((int)c.size() == mx) {
            auto it = lower_bound(all.begin(), all.end(), c);
            if (*it == c) {
                tr.push_back(c);
            }
        }
    }
    sort(tr.begin(), tr.end());
    tr.erase(unique(tr.begin(), tr.end()), tr.end());
    if ((int)tr.size() == 0) {
        cout << 0 << " " << 0 << endl;
        return 0;
    }
    cout << mx << " " << (int)tr.size() << endl;
    return 0;
}
