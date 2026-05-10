#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e6 + 5;
int tree[MAX];

void add(int i, int x) {
    for (; i < MAX; i = (i | (i + 1))) tree[i] += x;
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) ans += tree[i];
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    vector<int> cs;
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
        cs.push_back(all[i].first);
        cs.push_back(all[i].second);
    }
    cs.push_back(-1);
    sort(cs.begin(), cs.end());
    for (auto & [x, y] : all) {
        x = lower_bound(cs.begin(), cs.end(), x) - cs.begin();
        y = lower_bound(cs.begin(), cs.end(), y) - cs.begin();
    }
    vector<pair<int, int>> sx(n);
    vector<pair<int, int>> sy(n);
    for (int i = 0; i < n; ++i) {
        sx[i] = {all[i].first, i};
        sy[i] = {all[i].second, i};
    }
    sort(sx.begin(), sx.end());
    sort(sy.begin(), sy.end());
    vector<int> prx(n + 1);
    vector<int> pry(n + 1);
    prx[0] = 0;
    pry[0] = 0;
    for (int i = 0; i < n; ++i) {
        prx[i + 1] = max(prx[i], all[sx[i].second].second);
        pry[i + 1] = max(pry[i], all[sy[i].second].first);
    }
    vector<int> ans(n);
    vector<pair<int, int>> t_get(n);
    vector<int> cxgo(n + 1, n);
    vector<int> cygo(n + 1, n);
    for (int i = n - 1; i >= 0; --i) {
        auto [x, inx] = sx[i];
        auto [y, iny] = sy[i];
        int jx = upper_bound(sx.begin(), sx.end(), pair<int, int> {x, n + 1}) - sx.begin();
        int jy = upper_bound(sy.begin(), sy.end(), pair<int, int> {y, n + 1}) - sy.begin();
        int my = prx[jx];
        int mx = pry[jy];
        int jansx = upper_bound(sx.begin(), sx.end(), pair<int, int>{mx, n + 1}) - sx.begin() - 1;
        int jansy = upper_bound(sy.begin(), sy.end(), pair<int, int>{my, n + 1}) - sy.begin() - 1;
        cxgo[i] = i;
        cygo[i] = i;
        //cout << i << " " << my << " " << mx << " " << jansx << " " << jansy << endl;
        cxgo[i] = max(cxgo[i], cxgo[max(0ll, jansx)]);
        cygo[i] = max(cygo[i], cygo[max(0ll, jansy)]);
    }
    for (int i = 0; i < n; ++i) {
        if (cxgo[i] == n - 1) {
            ans[sx[i].second] = 1;
        }
        if (cygo[i] == n - 1) {
            ans[sy[i].second] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (ans[i]) {
            cout << "W";
        } else {
            cout << "L";
        }
    }
    cout << endl;
    return 0;
}
