#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    pair<int, int> u = {-1, -1}, v = {-1, -1};
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'G') {
            u.second = i;
            if (u.first == -1) u.first = i;
        } else {
            v.second = i;
            if (v.first == -1) v.first = i;
        }
    }
    if (u.first == -1 || v.first == -1) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 0;
    if (a[u.first] >= u.second) {
        for (int i = 0; i < u.first; ++i) {
            if (s[i] == 'H' && a[i] >= u.first) {
                ans++;
            }
        }
    }
    if (a[v.first] >= v.second) {
        for (int i = 0; i < v.first; ++i) {
            if (s[i] == 'G' && a[i] >= v.first) {
                ans++;
            }
        }
    }
    //cout << ans << endl;
    if (a[u.first] >= u.second && a[v.first] >= v.second) {
        if (a[u.first] >= v.first && v.first >= u.first || a[v.first] >= u.first && u.first >= v.first) {
            ans += 0;
        } else {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
