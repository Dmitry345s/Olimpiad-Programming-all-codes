#include<bits/stdc++.h>

using namespace std;

const int MAX = 100;
bitset<MAX> a[MAX];

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        int l;
        cin >> l;
        for (int j = 0; j < l; ++j) {
            int u;
            cin >> u;
            --u;
            a[i][u] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (c[i] >= c[j]) {
                if ((a[i] | a[j]) == a[j]) {
                    if (c[i] > c[j] || (a[i] & a[j]) != a[j]) {
                        cout << "Yes" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "No" << endl;
    return 0;
}
