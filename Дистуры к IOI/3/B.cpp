#include<bits/stdc++.h>

//#pragma GCC optimize("O3,unroll-loops")

#define int long long

using namespace std;

const int INF = 4e18 + 1, INF2 = 4e18;

struct Line{
    int k, b;
    Line(int k = 0, int b = 0) : k(k), b(b) {}
    int get(int x) {
        return k * x + b;
    }
};

int cross(Line a, Line b) {
    int db = a.b - b.b;
    int dk = b.k - a.k;
    if (db < 0) {
        db *= -1;
        dk *= -1;
    }
    int d = db / dk;
    if ((d - 1) * dk > db) return d - 1;
    if (d * dk > db) return d;
    return d + 1;
}

const int MAX = 1e6 + 2;
int fl = 0;

int st[MAX];
Line lns[MAX];

void add(Line a) {
    while (fl > 0 && cross(lns[fl - 1], a) <= st[fl - 1]) {
        fl--;
    }
    if (fl == 0) {
        st[fl] = -INF;
        lns[fl] = a;
        fl++;
    } else {
        st[fl] = cross(lns[fl - 1], a);
        lns[fl] = a;
        fl++;
    }
}

pair<int, int> tr(vector<int> v, int n, int x, int c) {
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + v[i];
    }
    vector<pair<int, int>> dp(n + 1);
    fl = 0;
    add(Line(0, 0));
    int tt = 0;
    int j = 0;
    for (int i = 1; i <= n; ++i) {
        int y = 2 * i * pref[i] + 2 * i * c + x;
        tt = min(fl, tt);
        while(tt < fl && st[tt] <= 2 * i) tt++;
        tt--;
        int yy = lns[tt].get(2 * i);
        //fl = upper_bound(st.begin(), st.end(), 2 * i) - st.begin() - 1;
        while (j < n + 1 && pref[j] < -lns[tt].k) j++;
        //j = lower_bound(pref.begin(), pref.end(), -lns[tt].k) - pref.begin();
        //cout << i << " " << j << endl;
        dp[i] = {y + yy, dp[j].second + 1};
        add(Line(-pref[i], dp[i].first));
        //cout << dp[i].first << " " << dp[i].second << endl;
    }
    return dp.back();
}

pair<int, int> tr2(vector<int> v, int n, int x, int c) {
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + v[i];
    }
    vector<pair<int, int>> dp(n + 1, {INF, -1});
    //st.clear();
    //lns.clear();
    dp[0] = {0, 0};
    //add(Line(0, 0));
    for (int i = 1; i <= n; ++i) {
        int y = 2 * i * pref[i] + 2 * i * c + x;
        for (int j = 0; j < i; ++j) {
            if (y + -pref[j] * 2 * i + dp[j].first < dp[i].first) {
                dp[i] = {y + -pref[j] * 2 * i + dp[j].first, dp[j].second + 1};
            } else if (y + -pref[j] * 2 * i + dp[j].first == dp[i].first) {
                dp[i].second = min(dp[i].second, dp[j].second + 1);
            }
        }
        //add(Line(-pref[i], dp[i].first));
        //cout << dp[i].first << " " << dp[i].second << endl;
    }
    return dp.back();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, k, c;
    cin >> n >> k >> c;
    vector<int> v(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        long long u;
        cin >> u;
        v[i] = u;
        cnt += v[i] * (i + 1);
    }
    int l = 0, r = INF2;
    while (l + 1 < r) {
        //cout << l << " " << r << endl;
        int m = (l + r) / 2;
        auto now = tr(v, n, m, c);
        if (now.second < k) {
            r = m;
        } else {
            l = m;
        }
    }
    //cout << r << endl;
    auto ans = tr(v, n, r, c);
    assert(ans.second <= k);
    //cout << ans.first << " " << ans.second << endl;
    cout << (long long)(ans.first - min(k, tr(v, n, 0, c).second) * r - cnt) << endl;
    return 0;
}
