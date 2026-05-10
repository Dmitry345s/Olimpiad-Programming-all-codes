#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int p = 1791791791;

vector<int> get(string s) {
    vector<int> ans((int)s.size() / 2);
    vector<int> z((int)s.size());
    z[0] = 0;
    int l = 0, r = 1;
    for (int i = 1; i < (int)s.size(); ++i) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < (int)s.size() && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (r < z[i] + i) {
            l = i;
            r = i + z[i];
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i){
        if (z[i + (int)ans.size() + 1] + i + (int)ans.size() + 1 == (int)s.size()) {
            ans[i] = 1;
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    map<ull, int> mp;
    long long ans = 0;
    vector<string> anss(n);
    for (int _ = 0; _ < n; ++_) {
        int now;
        cin >> now;
        string s;
        cin >> s;
        anss[_] = s;
        string s2 = s;
        reverse(s2.begin(), s2.end());
        string s3 = s2 + '#' + s;
        vector<int> ch = get(s3);
        ull h = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            h *= p;
            h += (s[i] - 'a' + 1);
        }
        mp[h]++;
    }
    //cout << ans << endl;
    map<ull, int> mp2;
    for (int _ = n - 1; _ >= 0; --_) {
        string s = anss[_];
        string s2 = s;
        reverse(s2.begin(), s2.end());
        string s3 = s2 + '#' + s;
        vector<int> ch = get(s3);
        ull h = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (ch[i] == 1) {
                ans += mp[h] * 2;
                //cout << _ << " " << i << " " << mp[h] << endl;
            }
            h *= p;
            h += (s[i] - 'a' + 1);
        }
        ans += mp[h];
    }
    cout << ans << endl;
    return 0;
}

