#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MOD = 998244353, W = 31, MXL = 23, INW = 128805723, INW2 = 499122177;

int fpow(int a, int x) {
    int ans = 1;
    while (x != 0) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

vector<int> ppf(vector<int> a, int n, int w) {
    //cout << "! " << n << " " << w << endl;
    if (n == 0) {
         return {a[0]};
    }
    vector<int> l, r;
    for (int i = 0; i < (1 << n); ++i) {
        if ((i & 1)) {
            r.push_back(a[i]);
        } else {
            l.push_back(a[i]);
        }
    }
    vector<int> ansl = ppf(l, n - 1, (w * w) % MOD);
    vector<int> ansr = ppf(r, n - 1, (w * w) % MOD);
    int wt = 1;
    vector<int> ansa((1 << n));
    for (int i = 0; i < (1 << n); ++i) {
        ansa[i] = (ansl[i % (1 << (n - 1))] + wt * ansr[i % (1 << (n - 1))]) % MOD;
        wt = (wt * w) % MOD;
    }
    return ansa;
}

vector<int> rpf(vector<int> c, int n, int w) {
    vector<int> cr = ppf(c, n, w);
    int cst = fpow((1 << n), MOD - 2);
    //cout << (cst * (1 << n)) % MOD << endl;
    for (int i = 0; i < (1 << n); ++i) {
        //cout << cr[i] << endl;
        cr[i] = (cr[i] * cst) % MOD;
    }
    return cr;
}

vector<int> fft(vector<int> a, vector<int> b, int n) {
    int w = W;
    int inw = INW;
    for (int i = n; i < MXL; ++i) {
        w = (w * w) % MOD;
        inw = (inw * inw) % MOD;
    }
    ////cout << fpow(W, (1 << 23)) << endl;
    int x = (w * w) % MOD;
    int x2 = (inw * inw) % MOD;
    ////cout << x << endl;
    //cout << w << " " << inw << " " << (w * inw) % MOD << " " << (x * x) % MOD << " " << (x2 * inw) % MOD << endl;
    vector<int> c1 = ppf(a, n, w);
    vector<int> c2 = ppf(b, n, w);
    for (int i = 0; i < (1 << n); ++i) {
        //cout << c1[i] << " " << c2[i] << endl;
        c1[i] = (c1[i] * c2[i]) % MOD;
        //cout << c1[i] << endl;
    }
    //cout << "#" << endl;
    return rpf(c1, n, inw);
}

signed main() {
    //cout << (4 + (1ll * 825076917 * 86583718) % MOD + (1ll * 173167436 * 911660635) % MOD) % MOD << endl;
    int n;
    cin >> n;
    vector<int> a((1 << n));
    vector<int> b((1 << n));
    for (int i = 0; i < (int)a.size(); ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < (1 << n); ++i) {
        a.push_back(0);
        b.push_back(0);
    }
    vector<int> c = fft(a, b, n + 1);
    for (int i = 0; i < (1 << (n + 1)); ++i) {
        cout << c[i] << " ";
    }
    cout << endl;
    return 0;
}
