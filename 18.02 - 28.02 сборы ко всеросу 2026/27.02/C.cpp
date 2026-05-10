#include<bits/stdc++.h>

using namespace std;

const int INF = 2e9;

int tr_f(vector<int> & a, vector<int> & b) {
    int n = (int)a.size();
    int dp[n + 1][2 * n + 1];
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][n] = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            if (j < 2 * n) dp[i + 1][j + 1] += min(dp[i][j], a[i]);
            if (j > 0) dp[i + 1][j - 1] += min(dp[i][j], b[i]);
        }
    }
    return dp[n][n];
}

int solve(set<pair<int, int>> all, int l, int r) {
    int ans = 0;
    while (true) {
        auto it = all.begin();
        cout << r << " " << l << " " << (r - l) / 2 << endl;
        vector<pair<int, int>> now;
        vector<pair<int, int>> now2;
        for (int i = 0; i < (r - l) / 2; ++i) {
            cout << (*it).first << " " << (*it).second << endl;
            now.push_back(*it);
            it++;
        }
        for (int i = 0; i < (r - l) / 2; ++i) {
            cout << (*it).first << " " << (*it).second << endl;
            now2.push_back(*it);
            it++;
        }
        //for (auto & val : now) val.first *= -1;
        //for (auto & val : now2) val.first *= -1;
        swap(now, now2);
        int fl = 1;
        for (auto & val : now) {
            cout << val.first << " " << val.second << endl;
            if (val.first == 0) {
                fl = 0;
                break;
            }
            val.first -= 1;
        }
        for (auto & val : now2) {
            cout << val.first << " " << val.second << endl;
            if (val.second == 0) {
                fl = 0;
                break;
            }
            val.second -= 1;
        }
        ans += fl;
        cout << fl << endl;
        if (!fl) break;
        all.clear();
        for (auto val : now) {
            cout << val.first << " " << val.second << endl;
            all.insert(val);
        }
        for (auto val2 : now2) {
            cout << val2.first << " " << val2.second << endl;
            all.insert(val2);
        }
    }
    return ans;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b(n);
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < q; ++i) {
        vector<int> na, nb;
        int l, r;
        cin >> l >> r;
        r++;
        set<pair<int, int>> all;
        set<pair<int, int>> all2;
        for (int i = l; i < r; ++i) {
            na.push_back(a[i]);
            nb.push_back(b[i]);
            all.insert({a[i], b[i]});
            all2.insert({b[i], a[i]});
        }
        int ans = max(solve(all, l, r), solve(all2, l, r));
        cout << solve(all2, l, r) << endl;
    }
    return 0;
}
