#include<bits/stdc++.h>

using namespace std;

double EPS = 1e-6;
double lx, ly, lz;

double ch3(double x, double y, double z, vector<array<int, 3>> & a) {
    double minm = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        double len = sqrt((x - a[i][0]) * (x - a[i][0]) + (y - a[i][1]) * (y - a[i][1]) + (z - a[i][2]) * (z - a[i][2]));
        minm = max(len, minm);
    }
    return minm;
}

double ch2(double x, double y, vector<array<int, 3>> & a) {
    double l = -1e4, r = 1e4;
    while (l + EPS < r) {
        double m1 = (2 * l + r) / 3;
        double m2 = (l + 2 * r) / 3;
        if (ch3(x, y, m1, a) < ch3(x, y, m2, a)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    lz = l;
    return ch3(x, y, lz, a);
}

double ch1(double x, vector<array<int, 3>> & a) {
    double l = -1e4, r = 1e4;
    while (l + EPS < r) {
        double m1 = (2 * l + r) / 3;
        double m2 = (l + 2 * r) / 3;
        if (ch2(x, m1, a) < ch2(x, m2, a)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ly = l;
    return ch2(x, ly, a);
}

signed main() {
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    double l = -1e4, r = 1e4;
    while (l + EPS < r) {
        double m1 = (2 * l + r) / 3;
        double m2 = (l + 2 * r) / 3;
        if (ch1(m1, a) < ch1(m2, a)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    lx = l;
    double q = ch1(l, a);
    if (q == 0 || q != 0) {
        cout << setprecision(20) << lx << " " << ly << " " << lz << endl;
    }
    return 0;
}
