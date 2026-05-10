#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    int last = -1;
    vector<int> l(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') {
            last = i;
        }
        l[i] = last - i;
    }
    vector<int> r(n);
    last = n;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '#') {
            last = i;
        }
        r[i] = last - i;
    }
    int minm = 0, maxm = 0, now = 0;
    for (int i = 0; i < m; ++i) {
        if (t[i] == 'L') {
            now--;
        } else {
            now++;
        }
        minm = min(minm, now);
        maxm = max(maxm, now);
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'D') {
            if (minm > l[i] && maxm < r[i]) {
                ans.push_back(i);
            }
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
