#include<bits/stdc++.h>

using namespace std;

int get(int x, int n, int p = 1) {
    if (x == 1) {
        return n;
    }
    if (x == 2) {
        return n - 1;
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x = i;
        while (x != 0) {
            a[x]++;
            if (x % 2 == 1) {
                x--;
            } else {
                x /= 2;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " " << get(i, n) << endl;
    }
    return 0;
}
