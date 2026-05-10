#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    set<int> w, b;
    string s;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'W') {
            w.insert(i);
        } else {
            b.insert(i);
        }
    }
    unordered_map<int, int> ws, bs;
    for (int v : w) {
        for (int v2 : w) {
            if (v2 <= v) continue;
            ws[v + v2]++;
        }
    }
    for (int v : b) {
        for (int v2 : b) {
            if (v2 <= v) continue;
            bs[v + v2]++;
        }
    }
    int bad2 = 0;
    if (n % 3 == 0) {
        for (int i = 0; i < n; ++i) {
            if (s[i] == s[(i + n / 3) % n] && s[i] == s[(i + 2 * n / 3) % n]) {
                bad2++;
            }
        }
    }
    bad2 /= 3;
    for (int i = 0; i < m; ++i) {
        int in;
        cin >> in;
        --in;
        if (n % 3 == 0 && s[in] == s[(in + n / 3) % n] && s[in] == s[(in + 2 * n / 3) % n]) bad2--;
        if (s[in] == 'W') {
            w.erase(in);
            for (int v : w) {
                ws[v + in]--;
            }
            for (int v : b) {
                bs[v + in]++;
            }
            b.insert(in);
            s[in] = 'B';
        } else {
            b.erase(in);
            for (int v : b) {
                bs[v + in]--;
            }
            for (int v : w) {
                ws[v + in]++;
            }
            w.insert(in);
            s[in] = 'W';
        }
        if (n % 3 == 0 && s[in] == s[(in + n / 3) % n] && s[in] == s[(in + 2 * n / 3) % n]) bad2++;
        int ans = 0;
        for (int j = 0; j < n; ++j) {
            if (s[j] == 'W') {
                ans += ws[2 * j] + ws[2 * j - n] + ws[2 * j + n];
            } else {
                ans += bs[2 * j] + bs[2 * j - n] + bs[2 * j + n];
            }
        }
        cout << ans - 2 * bad2 << endl;
    }
    return 0;
}
