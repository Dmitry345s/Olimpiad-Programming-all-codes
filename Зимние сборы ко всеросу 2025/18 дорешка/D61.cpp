#include<bits/stdc++.h>

using namespace std;

int gt(string s) {
    vector<int> z((int)s.size());
    z[0] = 0;
    int l = 0, r = 1;
    int mx = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < (int)s.size() && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (z[i] + i >= r) {
            l = i;
            r = i + z[i];
        }
        mx = max(mx, z[i]);
    }
    return mx;
}

signed main() {
    string s;
    cin >> s;
    string t;
    int ans = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        t.push_back(s[i]);
        reverse(t.begin(), t.end());
        int cnt = gt(t);
        ans += (int)t.size() - cnt;
        reverse(t.begin(), t.end());
    }
    cout << ans << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            char c;
            cin >> c;
            t.push_back(c);
            reverse(t.begin(), t.end());
            int cnt = gt(t);
            ans += (int)t.size() - cnt;
            reverse(t.begin(), t.end());
        } else {
            int cnt = gt(t);
            ans -= (int)t.size() - cnt;
            t.erase(t.begin());
        }
        cout << ans << endl;
    }
    return 0;
}
