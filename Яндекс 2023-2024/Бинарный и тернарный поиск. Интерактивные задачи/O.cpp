#include<bits/stdc++.h>

using namespace std;

double EPS = 1e-4;

double check2(double x, double y, vector<pair<int, int>> & a, int & k) {
    vector<double> p;
    for (int i = 0; i < (int)a.size(); ++i) {
        p.push_back(sqrt((x - a[i].first) * (x - a[i].first) + (y - a[i].second) * (y - a[i].second)));
    }
    sort(p.begin(), p.end());
    double ans = 0;
    for (int i = p.size() - 1; i > (int)p.size() - 1 - k; --i) {
        ans += p[i];
    }
    return ans;
}

double check(double x, vector<pair<int, int>> & a, int & k) {
    double l = -1001, r = 1001;
    while (l + EPS < r) {
        double m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        if (check2(x, m1, a, k) < check2(x, m2, a, k)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return check2(x, (l + r) / 2, a, k);
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    double l = -1001, r = 1001;
    while (l + EPS < r) {
        double m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        if (check(m1, a, k) < check(m2, a, k)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    cout << setprecision(20) << check((l + r) / 2, a, k) << endl;
    return 0;
}
