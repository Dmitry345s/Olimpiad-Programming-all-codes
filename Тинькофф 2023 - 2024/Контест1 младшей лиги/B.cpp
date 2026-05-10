#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int b;
    cin >> b;
    vector<int> ch(10, 1);
    for (int i = 0; i < b; ++i) {
        int c;
        cin >> c;
        ch[c] = 0;
    }
    int maxm = 0;
    for (int i = 0; i < 10; ++i) {
        if (ch[i]) {
            maxm = max(maxm, i);
        }
    }
    string x;
    cin >> x;
    int n = 0;
    for (int i = 0; i < x.size(); ++i) {
        n = (n * 10) + (x[i] - '0');
    }
    int now = 0;
    int ans = 1e18;
    int k = 1;
    for (int i = 0; i < x.size(); ++i) {
        int minm = 11, get = -1, c = (x[i] - '0');
        for (int j = 0; j < 10; ++j) {
            if (!ch[j]) continue;
            if (abs(c - j) < minm) {
                minm = abs(c - j);
                get = j;
            }
        }
        now = (now * 10) + get;
        if (get == 0) {
            k--;
        }
        if (now == 0) {
            ans = min(ans, n + 1);
        } else {
            ans = min(ans, abs(n - now) + i + k);
        }
    }
    int now2 = 0;
    int minm = x[0] - '0', get = 0, c = x[0] - '0';
    for (int j = 0; j < c; ++j) {
        if(!ch[j]) continue;
        if (abs(c - j) < minm) {
            minm = abs(c - j);
            get = j;
        }
    }
    now2 = get;
    k = 1;
    if (now2 == 0) k = 0;
    if (now2 == 0) {
        ans = min(ans, n + 1);
    } else {
        ans = min(ans, abs(n - now2) + k);
    }
    for (int i = 1; i < x.size(); ++i) {
        now2 = (now2 * 10) + maxm;
        if (maxm == 0) {
            k--;
        }
        if (now2 == 0) {
            ans = min(ans, n + 1);
        } else {
            ans = min(ans, abs(n - now2) + i + k);
        }
    }
    cout << ans << endl;
    return 0;
}
