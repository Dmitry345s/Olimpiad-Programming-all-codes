#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int b, k, x, y;
    cin >> b >> k >> x >> y;
    vector<pair<int, int>> d(x);
    for (int i = 0; i < x; ++i) {
        cin >> d[i].first;
        d[i].second = i;
    }
    sort(d.rbegin(), d.rend());
    vector<pair<int, int>> p(y);
    for (int i = 0; i < y; ++i) {
        cin >> p[i].first;
        p[i].second = i;
    }
    sort(p.rbegin(), p.rend());
    vector<int> pref1(x + 1);
    for (int i = 1; i <= x; ++i) {
        pref1[i] = pref1[i - 1] + d[i - 1].first;
    }
    vector<int> pref2(y + 1);
    for (int i = 1; i <= y; ++i) {
        pref2[i] = pref2[i - 1] + p[i - 1].first;
    }
    int ans = 0;
    int in = 0;
    for (int i = 0; i <= min(x, k); ++i) {
        if ((pref1[i] + b) * (100 + pref2[min(k - i, y)]) >= ans) {
            ans = (pref1[i] + b) * (100 + pref2[min(k - i, y)]);
            in = i;
        }
    }
    cout << in << " " << min(k - in, y) << endl;
    for (int i = 0; i < in; ++i) {
        cout << d[i].second + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < min(k - in, y); ++i) {
        cout << p[i].second + 1 << " ";
    }
    cout << endl;
    return 0;
}
