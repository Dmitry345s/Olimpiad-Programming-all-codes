#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(k);
    for (int i = 0; i < k; ++i) {
        int c;
        cin >> c;
        a[i].assign(c, 0);
        for (int j = 0; j < c; ++j) {
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
    }
    vector<int> st;
    for (int i = 0; i < k; ++i) {
        st.push_back(i);
    }
    vector<int> ans(k, n + 1);
    do {
        vector<int> mans(k);
        vector<int> used(n + 1);
        for (int i : st) {
            int now = 0;
            for (int i = n; i >= 0; --i) {
                if (!used[i]) {
                    now = i;
                    break;
                }
            }
            int t = now - a[i].back();
            mans[i] = t;
            for (int j = 0; j < (int)a[i].size(); ++j) {
                int x = a[i][j] + t;
                used[max(x, 0)] += 1;
            }
        }
        int fl = 1;
        for (int i = n; i > 0; --i) {
            if (used[i] == 0) {
                fl = 0;
            }
        }
        if (fl == 1) {
            ans = mans;
            break;
        }
    } while (next_permutation(st.begin(), st.end()));
    if (ans[0] == n + 1) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
