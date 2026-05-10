#include<bits/stdc++.h>

using namespace std;

void ask(int x, int & ch) {
    cout << x << endl;
    cin >> ch;
}

signed main() {
    int n;
    cin >> n;
    int l = 0, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int x;
        ask(m, x);
        if (x == 0) {
            return 0;
        } else if (x == 1) {
            l = m;
        } else {
            r = m;
        }
    }
    return 0;
}
