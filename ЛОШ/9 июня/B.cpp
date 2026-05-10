#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>

using namespace std;

bool check(double x, vector<double> a, double k) {
    double last = 0;
    for (int i = 0; i < int(a.size()) - 1; ++i) {
        if (a[i] - last > x) {
            return false;
        }
        last = min(last + x, double(a[i + 1]));
    }
    if (last < k) {
        return false;
    } else {
        return true;
    }
}

int main() {
    double k;
    int n;
    cin >> n >> k;
    vector<double> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    if (n == 2) {
        if (a[0] > k / 2) {
            cout << a[0] << endl;
        } else if (a[1] < k / 2) {
            cout << k - a[1] << endl;
        } else {
            cout << k / 2 << endl;
        }
        return 0;
    }
    a.push_back(k);
    double l = 0, r = k;
    while (l + 0.0000001 < r) {
        double m = (l + r) / 2;
        if (check(m, a, k)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << setprecision(20) << r << endl;
}
