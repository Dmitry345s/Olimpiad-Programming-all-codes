#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
    }
    vector<int> ans(m);
    ans[0] = a[0] + b[0] - 1;
    for (int i = 1; i < m; ++i) {
        int y = max(0ll, a[i] - ans[i - 1] - 1);
        ans[i] = ans[i - 1] + 1 + y + b[i] - 1;
    }
    cout << ans.back() << endl;
    return 0;
}
