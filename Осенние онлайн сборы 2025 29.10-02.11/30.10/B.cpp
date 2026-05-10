#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n - 1);
    int mxa = 0;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a[i];
        mxa = max(mxa, a[i]);
    }
    int q, f;
    cin >> q >> f;
    if (n <= 10 || mxa <= 100) {
        int nx = 0;
        vector<vector<int>> to_ans(n, vector<int> (mxa + 2));
        int nl = 0;
        vector<int> nh(n);
        while (nh[n - 1] < mxa + 1) {
            /*cout << nl << " " << nx << " ";
            for (int y = 0; y < n; ++y) {
                cout << nh[y] << " ";
            }
            cout << endl;*/
            if (nl < n - 1 && nh[nl] == a[nl]) {
                nl++;
                continue;
            }
            if (nh[nl] < a[nl - 1] && (nl == n - 1 || nh[nl] < a[nl])) {
                nx += 1;
                nh[nl] += 1;
                to_ans[nl][nh[nl]] = nx;
                continue;
            }
            vector<int> to_get;
            int u = nl;
            while (u >= 1 && nh[u] >= a[u - 1]) {
                to_get.push_back(u);
                --u;
            }
            to_get.push_back(u);
            nx += (int)to_get.size();
            for (auto v : to_get) {
                nh[v] += 1;
                to_ans[v][nh[v]] = nx;
            }
        }
        //cout << nx << endl;
        int c = 0;
        for (int i = 0; i < q; ++i) {
            int xc, j;
            cin >> xc >> j;
            j--;
            int x = xc - c;
            int ans;
            int u = upper_bound(to_ans[j].begin(), to_ans[j].end(), x) - to_ans[j].begin() - 1;
            if (u == mxa + 1) {
                ans = mxa + 1 + (x - to_ans[n - 1][mxa + 1]) / n;
            } else {
                ans = u;
            }
            cout << ans << endl;
            if (f == 2) {
                c = ans;
            }
        }
        return 0;
    }
    vector<int> pref(n);
    for (int i = 1; i < n; ++i) {
        pref[i] = a[i - 1] * i;
    }
    int c = 0;
    for (int i = 0; i < q; ++i) {
        int xc, j;
        cin >> xc >> j;
        --j;
        int x = xc - c;
        int ans;
        int u = upper_bound(pref.begin(), pref.end(), x) - pref.begin() - 1;
        if (j > u) {
            ans = 0;
        } else if (j == u) {
            ans = x - pref[u];
            if (u > 0) {
                if (x - pref[u] - a[u - 1] > 0) {
                    ans = a[u - 1] + (x - pref[u] - a[u - 1]) / (u + 1);
                }
            }
        } else {
            ans = a[u - 1];
            if (x - pref[u] - a[u - 1] > 0) {
                ans = a[u - 1] + (x - pref[u] - a[u - 1]) / (u + 1);
            }
        }
        cout << ans << endl;
        if (f == 2) {
            c = ans;
        }
    }

}
