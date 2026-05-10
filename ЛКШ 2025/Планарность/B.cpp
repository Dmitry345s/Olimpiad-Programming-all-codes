#include<bits/stdc++.h>

using namespace std;

signed main() {
    int _;
    cin >> _;
    string ch = "1111111111";
    string tt;
    getline(cin, tt);
    while (_--) {
        string s;
        getline(cin, s);
        //assert((int)s.size() > 0);
        if ((int)s.size() <= 6) {
            cout << "YES" << endl;
            continue;
        }
        if ((int)s.size() == 10) {
            if (s == ch) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
            continue;
        }
        int n = 6;
        vector<vector<int>> all(n, vector<int> (n));
        int x = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                all[i][j] = s[x] - '0';
                sum += all[i][j];
                x++;
            }
        }
        int fl = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (!all[i][j]) continue;
                vector<vector<int>> nowall = all;
                for (int j2 = 0; j2 < j; ++j2) {
                    nowall[i][j2] |= all[j][j2];
                }
                for (int j2 = j; j2 < i; ++j2) {
                    nowall[i][j2] |= all[j2][j];
                }
                for (int j2 = i; j2 < n; ++j2) {
                    nowall[j2][i] |= all[j2][j];
                }
                string now;
                for (int u = 0; u < n; ++u) {
                    for (int v = 0; v < u; ++v) {
                        if (u == j || v == j) continue;
                        now.push_back(nowall[u][v] + '0');
                    }
                }
                if (now == ch) {
                    fl = 0;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            string now;
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < u; ++v) {
                    if (u == i || v == i) continue;
                    now.push_back(all[u][v] + '0');
                }
            }
            if (now == ch) {
                fl = 0;
            }
        }
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> lf;
            vector<int> rg;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    lf.push_back(i);
                } else {
                    rg.push_back(i);
                }
            }
            int cnt = 0;
            for (int v : lf) {
                for (int u : rg) {
                    if (all[v][u] || all[u][v]) {
                        cnt++;
                    }
                }
            }
            if (cnt == 9) {
                fl = 0;
            }
        }
        if (fl) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
