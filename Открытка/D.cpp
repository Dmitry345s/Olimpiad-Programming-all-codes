#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, t, s;
    cin >> n >> t >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, pair<int, int>> mp;
    vector<int> nm(n);
    for (int i = 0; i < n; ++i) {
        int ch2;
        if (a[i] >= t) {
            ch2 = 0;
        } else {
            ch2 = (t - a[i] + s - 1) / s;
        }
        nm[i] = ch2;
        //cout << nm[i] << " ";
    }
    //cout << endl;
    int ch = 0, chnow = 0;
    for (int i = n - 1; i > 0; --i) {
        //cout << ch << " " << chnow << endl;
        mp[a[i]].first = ch + 1;
        int ch2 = t - (s * (nm[i] + n - 1 - i - ch));
        int r = n - (lower_bound(a.begin(), a.end(), ch2) - a.begin());
        mp[a[i]].second = r;
        chnow += 1;
        ch += min(chnow, nm[i - 1] - nm[i]);
        chnow = max(chnow - (nm[i - 1] - nm[i]), 0ll);
    }
    //cout << endl;
    int ch2 = t - (s * (nm[0] + n - 1 - ch));
    int r = n - (lower_bound(a.begin(), a.end(), ch2) - a.begin());
    mp[a[0]].second = r;
    mp[a[0]].first = ch + 1;
    /*for (int i = 0; i < n; ++i) {
        cout << mp[a[i]].first << " " << mp[a[i]].second << endl;
    }*/
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int ch, num;
        cin >> ch >> num;
        if (mp[ch].first <= num && num <= mp[ch].second) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
