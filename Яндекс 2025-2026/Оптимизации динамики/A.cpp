#include<bits/stdc++.h>

# define int long long

using namespace std;

struct Line {
    int k, b;
    Line(int k = 0, int b = 0) : k(k), b(b) {}
    int get(int x) {
        return k * x + b;
    }
};

int cr(Line a, Line b) {
    int difb = b.b - a.b;
    int difk = a.k - b.k;
    int d = difb / difk;
    if (d * difk > difb) return d - 1;
    if ((d + 1) * difk > difb) return d;
    return d + 1;
}

const int INF = 1e18;
vector<int> to_ans;
vector<Line> ls;

void add(Line a) {
    while (!ls.empty() && cr(a, ls.back()) <= to_ans.back()) {
        ls.pop_back();
        to_ans.pop_back();
    }
    if (ls.empty()) {
        to_ans.push_back(-INF);
    } else {
        to_ans.push_back(cr(a, ls.back()));
    }
    ls.push_back(a);
}

int get(int x) {
    return ls[upper_bound(to_ans.begin(), to_ans.end(), x) - to_ans.begin() - 1].get(x);
}

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    sort(all.rbegin(), all.rend());
    vector<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        if (st.empty() || st.back().second < all[i].second) {
            st.push_back(all[i]);
        }
    }
    all = st;
    n = (int)all.size();
    vector<int> dp(n + 1);
    for (int i = 0; i < n; ++i) {
        add(Line(all[i].first, dp[i]));
        dp[i + 1] = get(all[i].second);
    }
    cout << dp[n] << endl;
    return 0;
}
