#include<bits/stdc++.h>

using namespace std;

const int K = 1;

vector<int> solve1(vector<int> & a, int n) {
    int len = a.back() - a[0];
    vector<int> ans(len + 1, 0);
    for (int c = 1; c <= len; ++c) {
        int l = 0;
        int cnt = 0;
        while (l < (int)a.size()) {
            int st = a[l];
            int u = a[l] + c;
            int j = upper_bound(a.begin(), a.end(), u) - a.begin();
            cnt++;
            l = j;
        }
        ans[c] = cnt;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        all[a[i]].push_back(i);
    }
    vector<int> ans(n + 1);
    vector<int> an(n + 3);
    for (int i = 0; i < n; ++i) {
        if ((int)all[i].size() >= K) {
            vector<int> rans = solve1(all[i], n);
            for (int i = 0; i < (int)rans.size(); ++i) {
                ans[i] += rans[i];
            }
            an[(int)rans.size()] += 1;
        }
    }
    int now = 0;
    for (int i = 1; i <= n; ++i) {
        now += an[i];
        cout << ans[i] + now << endl;
    }
    cout << endl;
    return 0;
}
