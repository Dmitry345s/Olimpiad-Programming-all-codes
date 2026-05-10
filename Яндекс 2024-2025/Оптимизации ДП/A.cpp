#include<bits/stdc++.h>

# define int long long

using namespace std;

struct Line {
    int k, b;
    Line(int k, int b) : k(k), b(b) {}
    int get(int x) {
        return k * x + b;
    }
};

int operator + (Line a, Line b) {
    int u = b.b - a.b;
    int d = a.k - b.k;
    if (d < 0) {
        u *= -1;
        d *= -1;
    }
    int c = u / d;
    if ((c - 1) * d >= u) return c - 1;
    if (c * d >= u) return c;
    return c + 1;
}

vector<Line> st;
vector<int> all;

void add(Line a) {
    while ((int)st.size() > 0 && all.back() >= a + st.back()) {
        st.pop_back();
        all.pop_back();
    }
    if ((int)st.size() == 0) {
        st.push_back(a);
        all.push_back((long long)-2e18);
        return;
    }
    all.push_back(st.back() + a);
    st.push_back(a);
}

int get(int x) {
    return st[upper_bound(all.begin(), all.end(), x) - all.begin() - 1].get(x);
}

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    sort(all.begin(), all.end());
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        while ((int)a.size() > 0 && a.back().second <= all[i].second) {
            a.pop_back();
        }
        a.push_back(all[i]);
    }
    n = a.size();
    if (n == 1) {
        cout << a[0].first * a[0].second << endl;
        return 0;
    }
    vector<int> dp(n + 1);
    add(Line(a[0].second, dp[0]));
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = get(a[i].first);
        if (i != n - 1) {
            add(Line(a[i + 1].second, dp[i + 1]));
        }
    }
    cout << dp.back() << endl;
    return 0;
}
