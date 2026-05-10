#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

mt19937 rnd(179);

int det(vector<vector<int>> a) {
    int n = (int)a.size();
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i][i] == 0) {
            int fl = 0;
            for (int j = i + 1; j < n; ++j) {
                if (a[j][i] != 0) {
                    swap(a[i], a[j]);
                    ans = (ans * (MOD - 1)) % MOD;
                    fl = 1;
                }
            }
            if (!fl) return 0;
        }
        ans = (ans * a[i][i]) % MOD;
        int rev = fpow(a[i][i], MOD - 2);
        for (int j = 0; j < n; ++j) {
            a[i][j] = (a[i][j] * rev) % MOD;
        }
        for (int i2 = i + 1; i2 < n; ++i2) {
            int u = a[i2][i];
            for (int j = 0; j < n; ++j) {
                a[i2][j] = (a[i2][j] - (a[i][j] * u % MOD) + MOD) % MOD;
            }
        }
    }
    return ans;
}

signed main() {
    freopen("matchme.in", "r", stdin);
    freopen("matchme.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> all(n, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int u = rnd() % MOD;
        all[a][b] = u;
        all[b][a] = MOD - u;
    }
    if (det(all)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
