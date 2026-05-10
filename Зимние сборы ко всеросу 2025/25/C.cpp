#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    int l = 0, r = n + 1;
    while (l + 2 < r) {
        int c = (l + r) / 2;
        int c2 = c - 1;
        char ans1, ans2;
        cout << "? " << c << endl;
        cin >> ans1;
        cout << "? " << c2 << endl;
        cin >> ans2;
        if (ans1 == '<' && ans2 == '<') {
            l = c;
        } else if (ans1 == '>' && ans2 == '>') {
            r = c;
        }
    }
    return 0;
}
