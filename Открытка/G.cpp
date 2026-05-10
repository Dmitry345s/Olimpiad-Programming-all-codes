#include<bits/stdc++.h>

#define int long long

using namespace std;

bool check(int m, vector<int> a, int n, int c, int b) {
    vector<int> k(n);
    long long st = c * m;
    int flag2 = 1;
    for (int i = 0; i < n; ++i) {
        k[i] = a[i] - st;
        if (k[i] >= 0) {
            flag2 = 0;
        }
    }
    if (c > b) {
        if (!flag2) {
            return 0;
        }
        int p = c - b;
        int cnt = m;
        for (int i = 0; i < n; ++i) {
            if (k[i] < 0) {
                if (cnt > 0) {
                    cnt -= (abs(k[i]) - 1) / p;
                }
            }
        }
        return (cnt <= 0);
    } else if (c < b) {
        int p = b - c;
        int cnt = m;
        for (int i = 0; i < n; ++i) {
            if (k[i] >= 0) {
                cnt -= (k[i] + p) / p;
            }
        }
        return (cnt >= 0);
    }
    return flag2;
}

signed main() {
    int n, c, b;
    cin >> n >> c >> b;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    swap(c, b);
    int l = -1, r = 1e9 + 10;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(m, a, n, c, b)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << endl;
    return 0;
}
