#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int st = 1;
    while (true) {
        cout << st << endl;
        string ans;
        cin >> ans;
        if (ans == "wet") {
            st *= 2;
        } else {
            break;
        }
    }
    int l = st / 2, r = st;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        cout << m << endl;
        string ans;
        cin >> ans;
        if (ans == "wet") {
            l = m;
        } else {
            r = m;
        }
    }
    cout << "! " << r << endl;
    return 0;
}
