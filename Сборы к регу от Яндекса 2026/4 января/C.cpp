#include<bits/stdc++.h>

using namespace std;

const int LN = 31;

int get(int x, int pr) {
    if (x == 0) return 1;
    if (pr == 0) return 1;
    int st = -1;
    for (int i = LN - 1; i >= 0; --i) {
        if ((x >> i) & 1) {
            st = i;
            break;
        }
    }
    pr++;
    int mod1 = (1 << st);
    int mod2 = (2 << st);
    int fl = pr / mod2;
    int en = pr % mod2;
    int yy = fl - 1;
    int flen = fl * mod1;
    if (en > 0) {
        yy++;
    }
    if (en < mod1) {
        flen += en;
    } else {
        flen += mod1;
    }
    if ((mod1 - 1) & x) {
        yy = 0;
    }
    //cout << x << " " << pr << " " << x - (1 << st) << " " << flen - 1 << " " << yy << " " << fl << " " << en << endl;
    return get(x - (1 << st), flen - 1) + yy;
}

int f(int x, int l, int r) {
    //cout << x << " " << l << " " << r << " " << get(x, r) << " " << get(x, l) << endl;
    return get(x, r) - get(x, l) + ((x & l) == 0);
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        //cout << f(b, a, c) << endl;
        cout << f(b, a, c) + f(a, b, d) - ((a & b) == 0) << endl;
    }
    return 0;
}
