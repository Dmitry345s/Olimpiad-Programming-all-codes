#include<bits/stdc++.h>

using namespace std;

void ask(long long p, long long & f, long long & s) {
    cout << "X " << (1ll << p) << endl;
    cin >> f >> s;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        long long l = 0, r = 60;
        long long last = 1;
        while (l + 1 < r) {
            long long m = (l + r) / 2;
            long long f, s;
            ask(m, f, s);
            if (f == 0) {
                r = m;
            } else {
                last = s;
                l = m;
            }
        }
        cout << "N " << last << endl;
        string ch;
        cin >> ch;
        if (ch == "Wrong") {
            return 0;
        }
    }
    return 0;
}
