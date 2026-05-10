#include<bits/stdc++.h>

using namespace std;

signed main() {
    int g;
    cin >> g;
    //cout << (1ll << 59) << endl;
    while (g--) {
        int l = 0, r = 60;
        vector<pair<long long, long long>> get(62);
        long long to_ans = 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            cout << "X " << (1ll << m) << endl;
            long long a, b;
            cin >> a >> b;
            get[m] = {a, b};
            if (a == 0) {
                r = m;
            } else {
                to_ans = b;
                l = m;
            }
        }
        cout << "N " << to_ans << endl;
        string s;
        cin >> s;
        if (s == "Wrong") {
            return 0;
        }
    }
    return 0;
}
