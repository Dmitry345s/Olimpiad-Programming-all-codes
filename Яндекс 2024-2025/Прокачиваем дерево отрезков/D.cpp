#include<bits/stdc++.h>

# define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    vector<int> ans;
    for (int _ = 0; _ < n; ++_) {
        int t;
        cin >> t;
        if (t == 1) {
            a.push_back({1, 1});
            ans.push_back(-2);
        } else if (t == 4) {
            int i;
            cin >> i;
            --i;
            a.push_back(a[i]);
            ans.push_back(-2);
            if (a[i].second <= 0) {
                ans.back() = _;
            }
        } else if (t == 2) {
            int i;
            cin >> i;
            --i;
            if (a[i].second > 0) {
                a[i].first *= 2;
            }
        } else if (t == 3) {
            int i;
            cin >> i;
            --i;
            if (a[i].second > 0) {
                a[i].second *= 2;
            }
        } else {
            int i, j;
            cin >> i >> j;
            --i; --j;
            if (a[i].second > 0 && a[j].second > 0) {
                a[i].second -= a[j].first;
                a[j].second -= a[i].first;
                if (a[i].second <= 0) {
                    ans[i] = _;
                }
                if (a[j].second <= 0) {
                    ans[j] = _;
                }
            }
        }
    }
    cout << (int)ans.size() << endl;
    for (int v : ans) {
        cout << v + 1 << " ";
    }
    cout << endl;
    return 0;
}
