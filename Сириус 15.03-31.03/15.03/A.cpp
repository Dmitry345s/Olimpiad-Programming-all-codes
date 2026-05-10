#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    string s2;
    map<char, char> mp;
    for (int i = 0; i < 26; ++i) {
        mp[char(i + 97)] = s[i];
        s2 += char(i + 97);
    }
    int n;
    cin >> n;
    string t1, t2;
    cin >> t1 >> t2;
    map<char, char> mp2;
    for (int i = 0; i < n; ++i) {
        if (mp2.find(t1[i]) != mp2.end()) {
            if (mp2[t1[i]] != t2[i]) {
                cout << -1 << endl;
                return 0;
            }
        } else {
            mp2[t1[i]] = t2[i];
        }
    }
    int cnt = 0;
    while (cnt < 1e6) {
        int flag = 1;
        //cout << cnt << " " << s2 << endl;
        for (int i = 0; i < 26; ++i) {
            if (mp2.find(char(97 + i)) != mp2.end() && s2[i] != mp2[char(i + 97)]) {
                flag = 0;
            }
        }
        if (flag) break;
        for (int i = 0; i < 26; ++i) {
            s2[i] = mp[s2[i]];
            //cout << i << " " << s2[i] << endl;
        }
        //cout << endl;
        cnt++;
    }
    if (cnt == 1e6) {
        cout << -1 << endl;
    } else {
        cout << cnt << endl;
    }
    return 0;
}
