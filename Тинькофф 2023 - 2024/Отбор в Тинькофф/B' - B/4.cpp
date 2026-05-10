#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    int p, q;
    vector<int> a(n), b(n);
    cin >> p;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> q;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<bitset<1000000>> bagpr(n + 1);
    vector<vector<int>> bag(2, vector<int> (p, -1));
    bag[1][0] = 0;
    vector<int> cl(p, -1);
    for (int i = 1; i <= n; ++i) {
        bag[0] = bag[1];
        bag[1] = cl;
        for (int j = 0; j < p; ++j) {
            if (bag[0][j] != -1) {
                if (bag[0][j] > bag[1][j]) {
                    bag[1][j] = bag[0][j];
                    bagpr[i][j] = 0;
                }
                if (j + a[i - 1] < p) {
                    if (bag[0][j] + b[i - 1] > bag[1][j + a[i - 1]]) {
                        bag[1][j + a[i - 1]] = bag[0][j] + b[i - 1];
                        bagpr[i][j + a[i - 1]] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < p; ++i) {
        if (bag[1][i] >= q) {
            string ans = "";
            int sum = i;
            for (int j = n; j >= 1; --j) {
                if (!bagpr[j][sum]) {
                    ans += '0';
                } else {
                    ans += '1';
                    sum -= a[j - 1];
                }
            }
            reverse(ans.begin(), ans.end());
            cout << "NO" << endl;
            cout << ans << endl;
            return 0;
        }
    }
    vector<bitset<1000000>> bagpr2(n + 1);
    vector<vector<int>> bag2(2, vector<int> (q, -1));
    bag2[1][0] = 0;
    vector<int> cl2(q, -1);
    for (int i = 1; i <= n; ++i) {
        bag2[0] = bag2[1];
        bag2[1] = cl2;
        for (int j = 0; j < q; ++j) {
            if (bag2[0][j] != -1) {
                if (bag2[0][j] > bag2[1][j]) {
                    bag2[1][j] = bag2[0][j];
                    bagpr2[i][j] = 0;
                }
                if (j + b[i - 1] < q) {
                    if (bag2[0][j] + a[i - 1] > bag2[1][j + b[i - 1]]) {
                        bag2[1][j + b[i - 1]] = bag2[0][j] + a[i - 1];
                        bagpr2[i][j + b[i - 1]] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (bag2[1][i] >= p) {
            string ans = "";
            int sum = i;
            for (int j = n; j >= 1; --j) {
                if (!bagpr2[j][sum]) {
                    ans += '0';
                } else {
                    ans += '1';
                    sum -= b[j - 1];
                }
            }
            reverse(ans.begin(), ans.end());
            cout << "NO" << endl;
            cout << ans << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}
