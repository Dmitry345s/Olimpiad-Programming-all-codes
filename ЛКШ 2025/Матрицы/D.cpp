#include<bits/stdc++.h>

using namespace std;
using ld = long double;

const ld EPS = 1e-9;
const int MAX = 30;

int rfl = 1;
ld x[MAX];

void solve(vector<vector<ld>> a, vector<ld> b, int n) {
    for (int i = 0; i < n; ++i) {
        int fl = 0;
        for (int j = i; j < n; ++j) {
            if (abs(a[j][i]) >= EPS) {
                swap(a[i], a[j]);
                swap(b[i], b[j]);
                fl = 1;
                break;
            }
        }
        if (!fl) {
            rfl = 0;
            continue;
        }
        ld u = a[i][i];
        for (int j = 0; j < n; ++j) {
            a[i][j] /= u;
        }
        b[i] /= u;
        for (int i2 = i + 1; i2 < n; ++i2) {
            u = a[i2][i];
            for (int j = 0; j < n; ++j) {
                a[i2][j] -= a[i][j] * u;
            }
            b[i2] -= b[i] * u;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            b[i] -= x[j] * a[i][j];
            a[i][j] = 0;
        }
        if (abs(a[i][i]) < EPS) {
            if (abs(b[i]) < EPS) {
                rfl = 0;
                x[i] = 1;
            } else {
                rfl = -1;
                return;
            }
        } else {
            x[i] = b[i];
        }
    }
}

signed main() {
    freopen("linear.in", "r", stdin);
    freopen("linear.out", "w", stdout);
    int n;
    cin >> n;
    vector<vector<ld>> a(n, vector<ld> (n));
    vector<ld> b(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
        cin >> b[i];
    }
    //cout << -1 << endl;
    solve(a, b, n);
    if (rfl == -1) {
        cout << "impossible" << endl;
    } else if (rfl == 0) {
        cout << "infinity" << endl;
    } else {
        cout << "single" << endl;
        for (int i = 0; i < n; ++i) {
            cout << setprecision(20) << x[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
