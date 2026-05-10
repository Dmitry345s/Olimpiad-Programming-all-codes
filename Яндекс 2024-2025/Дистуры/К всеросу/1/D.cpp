#include<bits/stdc++.h>

#define double long double

using namespace std;

const int C = (1 << 29) - 1;

struct Line {
    double k, b;
    Line(double k = 0, double b = 0) : k(k), b(b) {};
    double get(double x) {
        return k * x + b;
    }
};

double operator+ (Line a, Line b) {
    return (a.b - b.b) / (b.k - a.k);
}

bool cmp(Line a, Line b) {
    return a.k > b.k;
}

vector<Line> cht;
vector<double> in;
const double INF = 2e18;

void add(Line a) {
    while ((int)cht.size() > 0 && cht.back() + a <= in.back()) {
        cht.pop_back();
        in.pop_back();
    }
    if ((int)cht.size() == 0) {
        in.push_back(-INF);
    } else {
        in.push_back(a + cht.back());
    }
    cht.push_back(a);
}

double get(double x) {
    return cht[upper_bound(in.begin(), in.end(), x) - in.begin() - 1].get(x);
}

signed main() {
    int n, q;
    cin >> n;
    vector<Line> ls;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == 0) continue;
        ls.push_back(Line((double)1 / (double)(a), -(double)b / (double)a));
    }
    sort(ls.rbegin(), ls.rend(), cmp);
    for (int i = 0; i < (int)ls.size(); ++i) {
        //cout << ls[i].k << " " << ls[i].b << endl;
        add(ls[i]);
    }
    int last = 0;
    cin >> q;
    for (int j = 0; j < q; ++j) {
        int e, f;
        cin >> e >> f;
        int c = e, d = f;
        if (last) {
            c ^= C;
            d ^= C;
        }
        double ans = get(d);
        if (ans < 0) {
            cout << "No cross" << endl;
            last = 1;
        } else {
            cout.precision(20);
            cout << ans << endl;
            last = 0;
        }
    }
    return 0;
}
