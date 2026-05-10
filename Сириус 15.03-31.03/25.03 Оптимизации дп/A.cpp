#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Line {
    int k, b;
    Line(int k = 0, int b = 0) : k(k), b(b){};
    int calc(int x) {
        return k * x + b;
    }
};

int tr(Line a, Line b) {
    int x = floor((long double)(b.b - a.b) / (a.k - b.k));
    return x;
}

vector<pair<int, int>> cht;
vector<Line> ls;

int get(int x) {
    //reverse(cht.begin(), cht.end());
    auto j = lower_bound(cht.rbegin(), cht.rend(), pair<int, int>{x, -1});
    int ans = ls[(*j).second].calc(x);
    //reverse(cht.begin(), cht.end());
    return ans;
}

void add(int p) {
    while (cht.size() > 0 && tr(ls[cht.back().second], ls[p]) > cht.back().first) {
        cht.pop_back();
    }
    if (cht.size() == 0) {
        cht.push_back({1e18, p});
    } else {
        cht.push_back({tr(ls[cht.back().second], ls[p]), p});
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    ls.resize(n + 1);
    vector<array<int, 3>> rc;
    for (int i = 0; i < n; ++i) {
        int x, y, a;
        cin >> x >> y >> a;
        rc.push_back({y, x, a});
    }
    sort(rc.begin(), rc.end());
    vector<int> dp(n);
    dp[0] = max(0ll, rc[0][1] * rc[0][0] - rc[0][2]);
    ls[0] = Line(-rc[0][0], dp[0]);
    add(0);
    for (int i = 1; i < n; ++i) {
        //cout << i << endl;
        dp[i] = max(0ll, get(rc[i][1])) + rc[i][1] * rc[i][0] - rc[i][2];
        if (i != n - 1) {
            ls[i] = Line(-rc[i][0], dp[i]);
            add(i);
        }
        //cout << dp[i] << endl;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
