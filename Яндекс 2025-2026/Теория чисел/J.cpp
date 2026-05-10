#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;
int us[MAX];
int cnt[MAX];

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        int a;
        cin >> a;
        us[a] = 1;
    }
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; j += i) {
            us[i] |= us[j];
        }
    }
    for (int i = 1; i < MAX; ++i) {
        if (us[i]) {
            cnt[i] = i - 1;
        }
    }
    int ans = 0;
    for (int i = 1; i < MAX; ++i) {
        ans += cnt[i];
        for (int j = 2 * i; j < MAX; j += i) {
            if (us[j]) {
                cnt[j] -= cnt[i];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
