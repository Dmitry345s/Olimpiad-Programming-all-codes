#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e3 + 5, INF = 1e18;
int a[MAX];

vector<int> solve(int l, int r, int num) {
    int mn = INF;
    int cnt = 0;
    for (int i = l; i < r; ++i) {
        mn = min(mn, a[i] - num);
    }
    vector<int> pos;
    for (int i = l; i < r; ++i) {
        if (a[i] - num == mn) {
            pos.push_back(i);
            cnt++;
        }
    }
    if (cnt == r - l) {
        vector<int> rans(r - l + 1, mn);
        rans[0] = 0;
        return rans;
    }
    pos.push_back(r);
    vector<pair<int, int>> all;
    int ls = l;
    int mx = 0;
    int in = -1;
    for (int rs : pos) {
        if (ls + 1 <= rs) {
            all.push_back({ls, rs});
            if (rs - ls > mx) {
                mx = rs - ls;
                in = (int)all.size() - 1;
            }
        }
        ls = rs + 1;
    }
    vector<int> rans(r - l + 1, INF);
    vector<int> tr = solve(all[in].first, all[in].second, num + mn);
    for (int i = 0; i < (int)tr.size(); ++i) {
        rans[i] = tr[i];
    }
    for (int i = 0; i < (int)all.size(); ++i) {
        if (in == i) continue;
        auto [nl, nr] = all[i];
        vector<int> nans = solve(nl, nr, num + mn);
        for (int j2 = (int)rans.size() - 1; j2 >= 0; --j2) {
            for (int j = 0; j < min(j2 + 1, (int)nans.size()); ++j) {
                rans[j2] = min(rans[j2 - j] + nans[j], rans[j2]);
            }
        }
    }
    for (int i = (int)rans.size() - 1; i >= cnt; --i) {
        rans[i] = rans[i - cnt] + mn;
    }
    for (int i = 1; i < cnt; ++i) {
        rans[i] = mn;
    }
    return rans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> ans = solve(0, n, 0);
    int rans = 0;
    for (int i = 0; i <= n; ++i) {
        if (ans[i] <= k) {
            rans = i;
        }
    }
    cout << rans << endl;
    return 0;
}
