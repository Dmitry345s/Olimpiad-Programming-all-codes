#include<bits/stdc++.h>

using namespace std;

signed main() {
    int MAX = 5001;
    vector<int> dp(MAX);
    set<int> ch;
    for (int i = 0; i < MAX; ++i) {
        ch.insert(i);
    }
    for (int i = 0; i < MAX; ++i) {
        vector<int> fans(MAX);
        for (int j = (i + 1) / 2; j < i; ++j) {
            fans[dp[j]] = 1;
        }
        for (int j = 0; j < MAX; ++j) {
            if (fans[j] == 0) {
                dp[i] = j;
                break;
            }
        }
    }
    int a, b, c;
    cin >> a >> b >> c;
    if ((dp[a] ^ dp[b] ^ dp[c]) == 0) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = (c + 1) / 2; i < c; ++i) {
        if ((dp[a] ^ dp[b] ^ dp[i]) == 0) {
            cout << "YES" << endl;
            cout << a << " " << b << " " << i << endl;
            return 0;
        }
    }
    for (int i = (b + 1) / 2; i < b; ++i) {
        if ((dp[a] ^ dp[i] ^ dp[c]) == 0) {
            cout << "YES" << endl;
            cout << a << " " << i << " " << c << endl;
            return 0;
        }
    }
    for (int i = (a + 1) / 2; i < a; ++i) {
        if ((dp[i] ^ dp[b] ^ dp[c]) == 0) {
            cout << "YES" << endl;
            cout << i << " " << b << " " << c << endl;
            return 0;
        }
    }
    return 0;
}
