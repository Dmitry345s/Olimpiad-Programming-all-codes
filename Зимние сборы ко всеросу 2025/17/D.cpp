#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5, LN = 17, MAX2 = (1 << LN);

vector<int> now[LN];

mt19937 rnd(179);

signed main() {
    int t;
    cin >> t;
    for (int i = 0; i < LN; ++i) {
        for (int j = 0; j < MAX2; j += (1 << (i + 1))) {
            for (int j2 = j; j2 < j + (1 << i); ++j2) {
                now[i].push_back(j2);
            }
        }
    }
    if (t == 1) {
        string s;
        cin >> s;
        int n = (int)s.size();
        if (n == 10) {
            for (int i = 0; i < n; ++i) {
                cout << s[i] << s[i] << s[i];
            }
            cout << endl;
            return 0;
        }
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = s[i] - '0';
        }
        for (int i = 0; i < LN; ++i) {
            int cnt = 0;
            for (int x : now[i]) {
                if (x < n) {
                    cnt ^= a[x];
                }
            }
            a.push_back(cnt);
        }
        for (int i = 0; i < (int)a.size(); ++i) {
            cout << a[i];
        }
        cout << endl;
    } else {
        string s;
        cin >> s;
        int m = (int)s.size();
        if (m == 30) {
            for (int i = 0; i < m; i += 3) {
                int cnt[2];
                cnt[0] = 0;
                cnt[1] = 0;
                cnt[s[i] - '0']++;
                cnt[s[i + 1] - '0']++;
                cnt[s[i + 2] - '0']++;
                if (cnt[0] > cnt[1]) {
                    cout << 0;
                } else {
                    cout << 1;
                }
            }
            cout << endl;
            return 0;
        }
        vector<int> b(m);
        for (int i = 0; i < m; ++i) {
            b[i] = s[i] - '0';
        }
        vector<int> u;
        vector<int> u2;
        for (int i = MAX; i < m; ++i) {
            u.push_back(b[i]);
        }
        for (int i = 0; i < LN; ++i) {
            b.pop_back();
            int cnt = 0;
            for (int x : now[i]) {
                if (x < MAX) {
                    cnt ^= b[x];
                }
            }
            u2.push_back(cnt);
        }
        if (u == u2) {
            for (int i = 0; i < MAX; ++i) {
                cout << b[i];
            }
            cout << endl;
            return 0;
        }
        int l = 0, r = MAX2;
        int cnt = 0;
        for (int i = LN - 1; i >= 0; --i) {
            //cout << u2[i] << " ";
            int m = (l + r) / 2;
            if (u[i] == u2[i]) {
                l = m;
            } else {
                cnt++;
                r = m;
            }
        }
        //cout << endl;
        if (r < MAX) {
            if (cnt == 1 && rnd() % 2 || cnt != 1) {
                b[l] ^= 1;
            }
        }
        for (int i = 0; i < MAX; ++i) {
            cout << b[i];
        }
        cout << endl;
    }
    return 0;
}
