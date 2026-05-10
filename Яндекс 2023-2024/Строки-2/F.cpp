#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

signed main() {
    long long p, q;
    cin >> p >> q;
    int cnt = 0;
    unordered_map<long long, string> mp;
    int cnt2 = 0;
    while (cnt <= 1e7) {
        cnt2 += 1;
        int sz = (rnd() % (rnd() % 100 + 1)) + 1;
        cnt += sz;
        long long hash1 = 0;
        string s;
        for (int i = 0; i < sz; ++i) {
            int c = rnd() % 26 + 97;
            //cout << c << endl;
            hash1 = ((hash1 * p) % q + c) % q;
            s.push_back(char(c));
        }
        if (mp.find(hash1) != mp.end() && mp[hash1] != s) {
            cout << mp[hash1] << endl;
            cout << s << endl;
            return 0;
        }
        mp[hash1] = s;
    }
    cout << cnt2 << endl;
    return 0;
}
