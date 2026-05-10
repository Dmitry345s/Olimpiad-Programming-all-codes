#include<bits/stdc++.h>

using namespace std;

signed main() {
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<char> s(m + 1);
    s[0] = char(getchar());
    for (int i = 0; i < m; ++i) {
        s[i] = char(getchar());
        //cout << s[i];
    }
    //if (m == 1e5 && n == 6.7e7 && s[0] == 'a') {
        //cout << (long long)(n - m + 1) * (n - m) / 2 << endl;
        //return 0;
    //}
    s[m] = '#';
    vector<int> p(100001);
    p[0] = 0;
    for (int i = 1; i < m + 1; i++) {
        p[i] = p[i - 1];
        while (p[i] > 0 && s[p[i]] != s[i]) {
            p[i] = p[p[i] - 1];
        }
        if (s[p[i]] == s[i]) p[i]++;
    }
    int last = p[m];
    long long ans = 0;
    char c;
    c = char(getchar());
    for (int i = 0; i < n; i++) {
        c = char(getchar());
        while (last > 0 && s[last] != c) {
            last = p[last - 1];
        }
        if (s[last] == c) last++;
        if (last == m) {
            //cout << i << endl;
            ans += i + 1 - m;
        }
    }
    cout << ans << '\n';
}
