#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e6 + 1;
int cnt[2 * MAX];

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int ans = 0;
    for (int j = 1; j < MAX; ++j) {
        for (int i = j; i < MAX; i += j) {
            if ((i ^ (i + j)) == j) {
                ans += cnt[i] * cnt[i + j];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
