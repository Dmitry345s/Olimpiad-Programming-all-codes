#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    vector<int> ans(n);
    for (int i = 0; i < 10; ++i) {
        cout << "? ";
        for (int j = 0; j < n; ++j) {
            cout << ((a[j] >> i) & 1);
        }
        cout << endl;
        string q;
        cin >> q;
        for (int j = 0; j < n; ++j) {
            int c = q[j] - '0';
            ans[j] |= (c << i);
        }
    }
    cout << "! ";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
