#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n - 2; ++i) {
        vector<int> b(n + 1);
        int cnt = 0;
        b[a[i]] += 1;
        b[a[i + 1]] += 1;
        if (b[a[i + 1]] == 1) {
            cnt++;
        }
        for (int j = i + 2; j < n; ++j) {
            b[a[j]] += 1;
            if (b[a[j]] == 1) {
                cnt++;
            } else if (b[a[j]] == 2) {
                cnt--;
            }
            if (b[a[i]] == 1 && b[a[j]] == 1) {
                ans += cnt - 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
