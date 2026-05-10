#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Line {
    int k, b;
    Line (int k = 0, int b = 0) : k(k), b(b){};
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
    int j = lower_bound(cht.begin(), cht.end(), pair<int, int>{x, -1}) - cht.begin() - 1;
    //cout << j << endl;
    return ls[cht[j].second].calc(x);
}

void add(int p) {
    while (cht.size() > 0 && tr(ls[cht.back().second], ls[p]) < cht.back().first) {
        cht.pop_back();
    }
    if (cht.size() == 0) {
        cht.push_back({-1e18, p});
    } else {
        cht.push_back({tr(ls[cht.back().second], ls[p]), p});
    }
}

signed main() {
    int n;
    cin >> n;
    ls.resize(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<int> dp(n);
    dp[0] = 0;
    ls[0] = Line(b[0], dp[0]);
    add(0);
    for (int i = 1; i < n; ++i) {
        dp[i] = get(a[i]);
        ls[i] = Line(b[i], dp[i]);
        add(i);
        //cout << dp[i] << endl;
    }
    cout << dp.back() << endl;
    return 0;
}
