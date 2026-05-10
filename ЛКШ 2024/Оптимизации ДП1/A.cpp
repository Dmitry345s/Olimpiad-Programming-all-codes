#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Line {
    long long k, b;
    Line(long long k, long long b) : k(k), b(b) {};
};

long long operator + (Line a, Line b) {
    long long c1 = b.b - a.b;
    long long c2 = a.k - b.k;
    long long d = c1 / c2;
    if (c2 < 0) {
        c1 *= -1;
        c2 *= -1;
    }
    if ((d - 1) * c2 >= c1) return d - 1;
    if (d * c2 >= c1) return d;
    return d + 1;
}

vector<long long> cht;
vector<Line> ls;

void add(Line a) {
    if ((long long)ls.size() == 0) {
        cht.push_back((long long)-INF);
        ls.push_back(a);
        return;
    }
    while (true) {
        long long now = ls.back() + a;
        if (now <= cht.back()) {
            ls.pop_back();
            cht.pop_back();
        } else {
            break;
        }
    }
    long long now = ls.back() + a;
    ls.push_back(a);
    cht.push_back(now);
}

long long get(long long x) {
    long long j = upper_bound(cht.begin(), cht.end(), x) - cht.begin();
    j--;
    return ls[j].k * x + ls[j].b;
}

signed main() {
    int n;
    cin >> n;
    vector<long long> b(n + 1);
    vector<long long> a(n);
    for (long long i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (long long i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    vector<long long> pr(n + 1);
    pr[0] = 0;
    for (long long i = 1; i <= n; ++i) {
        pr[i] = pr[i - 1] + a[i - 1];
        //cout << pr[i] << endl;
    }
    vector<long long> dp(n + 1, INF);
    dp[1] = 0;
    add(Line(b[1], dp[1]));
    for (long long i = 2; i <= n; ++i) {
        dp[i] = get(a[i - 1]);
        add(Line(b[i], dp[i]));
    }
    cout << dp.back() << endl;
    return 0;
}
