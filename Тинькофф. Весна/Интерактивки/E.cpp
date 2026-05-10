#include<iostream>
#include<vector>

using namespace std;

int main() {
    int k, n;
    cin >> k >> n;
    vector<int> p(n);
    int ans;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            cout << 1 << endl;
            cin >> ans;
            if (ans == 1) {
                p[i] = 1;
            } else if (ans == 0) {
                return 0;
            } else {
                p[i] = -1;
            }
        } else {
            cout << k << endl;
            cin >> ans;
            if (ans == -1) {
                p[i] = 1;
            } else if (ans == 0) {
                return 0;
            } else {
                p[i] = -1;
            }
        }
    }
    int l = 1, r = k;
    int i = 0;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        cout << m << endl;
        cin >> ans;
        ans *= p[i];
        if (ans == 0) {
            return 0;
        } else if (ans == -1) {
            r = m;
        } else {
            l = m;
        }
        ++i;
        if (i == n) {
            i = 0;
        }
    }
    cout << r << endl;
    return 0;
}
