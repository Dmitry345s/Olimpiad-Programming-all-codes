#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    if (k % 2 == 1) {
        cout << "NO" << endl;
        return 0;
    }
    vector<int> a(n + 1);
    int ch = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = i;
        ch += abs(i - (n - i + 1));
    }
    if (k > ch) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= (n / 2); ++i) {
        int now = abs(i - (n - i + 1)) * 2;
        if (now > k) {
            int j = k / 2 + i;
            swap(a[i], a[j]);
            break;
        } else {
            swap(a[i], a[n - i + 1]);
            k -= now;
        }
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
