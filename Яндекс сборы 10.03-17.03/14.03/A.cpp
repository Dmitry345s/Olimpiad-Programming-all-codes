#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> all;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all[a[i]].push_back(i);
    }
    vector<int> ans(n);
    int l = 0;
    while (l < n) {
        int u = all[a[l]].back();
        for (int j = l; j <= u; ++j) {
            ans[j] = a[l];
        }
        l = u + 1;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
