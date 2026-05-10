#include<bits/stdc++.h>

using namespace std;

struct Line {
    long long k, b;
    Line(long long k, long long b) : k(k), b(b) {};
};

long long operator + (Line a, Line b) {
    long long c1 = b.b - a.b, c2 = a.k - b.k;
    if (c2 < 0) {
        c1 *= -1;
        c2 *= -1;
    }
    long long d = c1 / c2;
    d = (c1 + c2 - 1) / c2;
    return d;
    //if ((d - 1) * c2 >= c1) return d - 1;
    //if (d * c2 >= c1) return d;
    //return d + 1;
}

vector<long long> cht;
vector<Line> now;

void add(Line a) {
    if ((int)now.size() == 0) {
        cht.push_back(-2e18);
        now.push_back(a);
        return;
    }
    while (true) {
        long long ls = now.back() + a;
        if (ls <= cht.back()) {
            now.pop_back();
            cht.pop_back();
        } else {
            break;
        }
    }
    cht.push_back(now.back() + a);
    now.push_back(a);
}

long long get(long long x) {
    int j = upper_bound(cht.begin(), cht.end(), x) - cht.begin();
    --j;
    return now[j].k * x + now[j].b;
}

signed main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> all(n);
    for (int i = 0; i < n; ++i) {
        long long w, h;
        cin >> w >> h;
        all[i] = {w, h};
    }
    sort(all.rbegin(), all.rend());
    vector<pair<long long, long long>> nall = {all[0]};
    for (int i = 1; i < n; ++i) {
        if (!(all[i].second <= nall.back().second)) {
            nall.push_back(all[i]);
        }
    }
    reverse(nall.begin(), nall.end());
    int nn = (int)nall.size();
    //cout << nn << endl;
    vector<long long> dp(nn + 1);
    dp[1] = nall[0].first * nall[0].second;
    //cout << dp[1] << endl;
    add(Line(nall[0].second, dp[0]));
    for (int i = 2; i <= nn; ++i) {
        dp[i] = min(get(nall[i - 1].first), nall[i - 1].first * nall[i - 1].second + dp[i - 1]);
        add(Line(nall[i - 1].second, dp[i - 1]));
    }
    cout << dp.back() << endl;
    return 0;
}
