#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(k);
        for (int i = 0; i < k; ++i) {
            cin >> a[i];
        }
        if (a.size() > 0 && a[0] == 1) {
            a.erase(a.begin());
        } else {
            a.insert(a.begin(), 1);
        }
        cout << n << " " << (int)a.size() << endl;
        for (int i = 0; i < a.size(); ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
