#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> mn, mx;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if (a < 10) {
            mn.push_back(a);
        } else {
            mx.push_back(a);
        }
    }
    sort(mn.rbegin(), mn.rend());
    sort(mx.rbegin(), mx.rend());
    int sz1 = (int)mx.size();
    int sz2 = (int)mn.size();
    vector<int> pref(sz1 + 1), pref2(sz2 + 1);
    for (int i = 0; i < sz1; ++i) {
        pref[i + 1] = pref[i] + mx[i];
    }
    for (int i = 0; i < sz2; ++i) {
        pref2[i + 1] = pref2[i] + mn[i];
    }
    int rans = 0;
    for (int j = 0; j < min(sz1, sz2) + 1; ++j) {
        int now = j;
        int ans = 0;
        ans += pref2[j] * 100;
        int y = sz1 - j;
        ans += pref[y / 2] * 100;
        ans += pref.back() - pref[(y + 1) / 2];
        int x = (sz2 - j);
        if (y % 2 == 1) {
            if (j < sz2) {
                ans += mx[y / 2] * 10;
            } else {
                ans += mx[y / 2];
            }
        }
        if (x % 2 == 1) {
            ans += (pref2[j + x / 2] - pref2[j]) * 10;
            ans += pref2.back() - pref2[j + x / 2];
        } else if (x != 0) {
            if (y % 2 == 1) {
                ans += (pref2[j + x / 2 - 1] - pref2[j]) * 10;
                ans += pref2.back() - pref2[j + x / 2 - 1];
            } else {
                ans += (pref2[j + x / 2] - pref2[j]) * 10;
                ans += pref2.back() - pref2[j + x / 2];
            }
        }
        rans = max(ans, rans);

    }
    cout << rans << endl;
    /*int sz1 = (int)mx.size();
    int ans = 0;
    for (int i = 0; i < sz1; ++i) {
        if (i < sz1 / 2) {
            ans += mx[i];
        }
        if (i >= (sz1 + 1) / 2) {
            ans += mx[i] * 100;
        }
    }
    if (sz1 % 2 == 1 && ((int)mn.size() != 0)) {
        int mx1 = mn[0] + mx[sz1 / 2] * 10;
        int mx2 = mn.back() * 100 + mx[sz1 / 2];
        if (mx1 > mx2) {
            mn.erase(mn.begin());
            ans += mx1;
        } else {
            mn.pop_back();
            ans += mx2;
        }
    } else if (sz1 % 2 == 1 && (int)mn.size() == 0) {
        ans += mx[sz1 / 2];
    }
    int sz2 = (int)mn.size();
    for (int i = 0; i < sz2; ++i) {
        if (i < (sz2 + 1) / 2) {
            ans += mn[i];
        }
        if (i >= (sz2 + 1) / 2) {
            ans += mn[i] * 10;
        }
    }*/
    //cout << ans << endl;
    return 0;
}
