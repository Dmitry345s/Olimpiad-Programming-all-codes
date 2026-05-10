#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> alla = {-1};
    vector<int> allb;
    vector<int> allc;
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + (s[i] == 'a');
        if (s[i] == 'a') {
            alla.push_back(i);
        } else if (s[i] == 'c') {
            allc.push_back(i);
        } else {
            allb.push_back(i);
        }
    }
    vector<int> suf(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = suf[i + 1] + (s[i] == 'c');
    }
    for (int i = 0; i < q; ++i) {
        int ql, qr;
        cin >> ql >> qr;
        --ql;
        int l = -1 + pref[ql], r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if ((int)alla.size() <= m) {
                r = m;
                continue;
            }
            int j = max(ql - 1, alla[m]);
            int y = upper_bound(allb.begin(), allb.end(), j) - allb.begin();
            //cout << j << " " << y << endl;
            if ((int)allb.size() <= y) {
                r = m;
                continue;
            }
            if (allb[y] >= qr || suf[allb[y]] - suf[qr] < m - pref[ql]) {
                r = m;
                continue;
            }
            l = m;
        }
        if (l == -1 + pref[ql]) {
            cout << 0 << endl;
        } else {
            cout << 2 * (l - pref[ql]) + 1 << endl;
        }
    }
    return 0;
}
