#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

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

int det(vector<vector<int>> a, int n) {
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        int fl = 0;
        for (int j = i; j < n; ++j) {
            //cout << a[j][i] << " ";
            if (a[j][i] != 0) {
                swap(a[i], a[j]);
                if (i != j) {
                    ans = (ans * (MOD - 1)) % MOD;
                }
                fl = 1;
                break;
            }
        }
        if (!fl) {
            return 0;
        }
        int rev = fpow(a[i][i], MOD - 2);
        //cout << a[i][i] << " " << rev << endl;
        ans = (ans * a[i][i]) % MOD;
        for (int j = 0; j < n; ++j) {
            a[i][j] = (a[i][j] * rev) % MOD;
        }
        //cout << a[i][i] << endl;
        for (int i2 = i + 1; i2 < n; ++i2) {
            int u = a[i2][i];
            for (int j = 0; j < n; ++j) {
                //cout << a[i][j] << " " << u << endl;
                //cout << a[i][j] * u % MOD << endl;
                a[i2][j] = (a[i2][j] - (a[i][j] * u % MOD) + MOD) % MOD;
            }
        }
        //cout << "#" << endl;
    }
    /*for (int i = n - 1; i >= 0; --i) {
        for (int i2 = i - 1; i2 >= 0; --i2) {
            for (int j = 0; j < n; ++j) {
                a[i2][j] = (a[i2][j] - (a[i][j] * a[i2][i]) % MOD + MOD) % MOD;
            }
        }
    }*/
    return ans;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n - 1, vector<int> (n - 1));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        --u; --v;
        if (u >= 0 && v >= 0) {
            a[u][v] = MOD - 1;
            a[v][u] = MOD - 1;
        }
        if (u >= 0) {
            a[u][u]++;
        }
        if (v >= 0) {
            a[v][v]++;
        }
    }
    cout << det(a, n - 1) << endl;
    return 0;
}
