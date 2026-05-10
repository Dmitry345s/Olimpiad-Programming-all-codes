#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e5 + 1, C = 31, INF = 1e9;
int a[MAX];

pair<int, int> ch(int lm, int n) {
    vector<pair<int, int>> dp(n + 1, {-INF * INF, 0});
    vector<pair<int, int>> mx(n + 1);
    vector<int> go(C, -1);
    pair<int, int> ldp = {0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < C; ++j) {
            if ((a[i] >> j) & 1) {
                go[j] = i;
            }
        }
        mx[i + 1] = max(mx[i], ldp);
        vector<int> now;
        for (int j = 0; j < C; ++j) {
            now.push_back(go[j]);
        }
        sort(now.begin(), now.end());
        now.erase(unique(now.begin(), now.end()), now.end());
        reverse(now.begin(), now.end());
        int aa = a[i];
        ldp = {-INF * INF, 0};
        for (int in : now) {
            if (in != -1) {
                aa |= a[in];
            }
            auto tr = mx[in + 1];
            int uu = tr.first + aa - lm;
            if (ldp.first < uu) {
                ldp.first = uu;
                ldp.second = tr.second + 1;
            }
        }
    }
    return ldp;
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int l = -INF, r = INF;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        pair<int, int> now = ch(m, n);
        if (now.second >= k) {
            l = m;
        } else {
            r = m;
        }
    }
    pair<int, int> ans = ch(l, n);
    cout << ans.first + k * l << endl;
    return 0;
}
