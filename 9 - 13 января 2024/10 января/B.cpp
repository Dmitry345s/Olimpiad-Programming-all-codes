#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int minm = 1e9, to = -1;
    for (int i = 0; i < 32; ++i) {
        int i2 = rnd() % n;
        int now = 0;
        int cnt = 0;
        for (int j = i; j < i + n; ++j) {
            int j2 = j % n;
            //cout << i << " " << a[j2] << " " << now << endl;
            if ((now & a[j2]) != 0) {
                cnt += 1;
                now = a[j2];
            } else {
                now = (now | a[j2]);
            }
        }
        if (cnt < minm) {
            minm = cnt;
            to = i;
        }
    }
    int now = 0, cnt = 0;
    int k = n;
    cout << minm + 1 << " " << to + 1 << endl;
    for (int j = to; j < to + n; ++j) {
        int j2 = j % n;
        if ((now & a[j2]) != 0) {
            now = a[j2];
            cout << cnt << " ";
            k -= cnt;
            cnt = 1;
        } else {
            now |= a[j2];
            cnt++;
        }
    }
    cout << k << endl;
    return 0;
}
