#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5, K = 320;
int MAX2 = (MAX + K - 1) / K;
int n;

vector<int> b(MAX);
vector<int> a(MAX), del(MAX), prec(MAX);

void build(vector<int> a) {
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
    }
    for (int i = 0; i < MAX2; ++i) {
        sort(b.begin() + min(n, i * K), b.begin() + min(n, (i + 1) * K));
    }
}

void rebuild(int l) {
    for (int i = l * K; i < min((l + 1) * K, n); ++i) {
        b[i] = a[i];
    }
    sort(b.begin() + l * K, b.begin() + min((l + 1) * K, n));
}

void upd(int l, int r, int x) {
    if (prec[l] == prec[r]) {
        for (int i = l; i <= r; ++i) {
            a[i] += x;
        }
        rebuild(prec[l]);
        return;
    }
    for (int i = l; i < min((prec[l] + 1) * K, n); ++i) {
        a[i] += x;
    }
    rebuild(prec[l]);
    for (int i = min(n, (prec[r]) * K); i <= r; ++i) {
        a[i] += x;
    }
    rebuild(prec[r]);
    for (int i = prec[l] + 1; i < prec[r]; ++i) {
        del[i] += x;
    }
}

int get(int l, int r, int x) {
    if (prec[l] == prec[r]) {
        int flag = 0;
        for (int i = l; i <= r; ++i) {
            if (a[i] + del[prec[i]] == x) {
                flag = 1;
            }
        }
        return flag;
    }
    int flag = 0;
    for (int i = l; i < min(n, (prec[l] + 1) * K); ++i) {
        if (a[i] + del[prec[i]] == x) {
            flag = 1;
        }
    }
    for (int i = (prec[r]) * K; i <= r; ++i) {
        if (a[i] + del[prec[i]] == x) {
            flag = 1;
        }
    }
    for (int i = prec[l] + 1; i < prec[r]; ++i) {
        int j = (lower_bound(b.begin() + min(i * K, n), b.begin() + min((i + 1) * K, n), x - del[i]) - b.begin());
        //cout << i << endl;
        //cout << j << endl;
        if (j < min((i + 1) * K, n) && j < (int)b.size() && b[j] == x - del[i]) {
            flag = 1;
        }
    }
    return flag;
}

signed main() {
    int m;
    cin >> n >> m;
    b.resize(n);
    MAX2 = (n + K - 1) / K;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        prec[i] = i / K;
    }
    build(a);
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int l, r, x;
            cin >> l >> r >> x;
            --l; --r;
            upd(l, r, x);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            --l; --r;
            if (get(l, r, x)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
