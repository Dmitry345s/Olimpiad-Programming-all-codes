#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const ull MOD = 1e9 + 7, P = 179;
const int MAX = 2e5;

ull pows[MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    pows[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = pows[i - 1] * P;
    }
    string s;
    cin >> s;
    int cnt = 0;
    unordered_map<ull, int> mp;
    vector<int> s2((int)s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
        s2[i] = s[i] - 'a' + 1;
    }
    for (int i = 0; i < (int)s.size(); ++i) {
        ull h = 0;
        for (int j = i; j < (int)s.size(); ++j) {
            h *= P;
            h += s2[j];
            cnt += ((++mp[h]) == 1);
        }
    }
    cout << cnt << '\n';
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            char c;
            cin >> c;
            s2.push_back(c - 'a' + 1);
            ull h = 0;
            for (int j = (int)s.size() - 1; j >= 0; --j) {
                h += pows[(int)s.size() - 1 - j] * s2[j];
                cnt += ((++mp[h]) == 1);
            }
        } else {
            ull h = 0;
            for (int j = 0; j < (int)s.size(); ++j) {
                h *= P;
                h += s2[j];
                cnt -= ((--mp[h]) == 0);
            }
            s.erase(s.begin());
        }
        cout << cnt << '\n';
    }
    return 0;
}
