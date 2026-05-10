#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, x;
    cin >> n >> x;
    x += (n + 1) * n / 2;
    vector<int> ans(n);
    ans[n - 1] = n;
    int now = n - 1;
    int now_sum = (n - 1) * n + 1;
    if (now_sum < x) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = n - 1; i > 0; --i) {
        //cout << now_sum << " " << x << endl;
        if (now == 0) break;
        if (now_sum - now + 1 >= x) {
            ans[now - 1] = i;
            now_sum -= now - 1;
            now = now - 1;
        } else {
            int j = now_sum - x;
            if (j == 0 && ans[j] != 0) break;
            //cout << j << endl;
            ans[j] = i;
            now = j;
            now_sum -= j;
        }
    }
    int last = 1;
    for (int i = 0; i < n; ++i) {
        if (ans[i] == 0) {
            cout << last << " ";
            last++;
        } else {
            cout << ans[i] << " ";
        }
    }
    return 0;
}
