#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s, t;
    cin >> s >> t;
    if ((int)s.size() < (int)t.size()) {
        cout << "NO" << endl;
        return 0;
    }
    if (s == t) {
        cout << "YES" << endl;
        return 0;
    }
    int in = (int)s.size() - 1;
    int fl = 1;
    int u = 0;
    while (u < (int)t.size() && s[u] == t[u]) {
        u++;
    }
    if (u % 2 == 0) {
        u--;
    }
    if (u < 0) {
        cout << "NO" << endl;
        return 0;
    }
    vector<int> us((int)s.size());
    for (int l = (int)t.size() - 1; l >= u; l--) {
        while (in > u && s[in] != t[l]) {
            --in;
        }
        if (in <= u) {
            cout << "NO" << endl;
            return 0;
        }
        --in;
    }
    cout << "YES" << endl;
    return 0;
}
