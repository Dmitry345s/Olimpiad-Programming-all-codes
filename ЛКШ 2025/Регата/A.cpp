#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        sum += a[i];
    }
    if (sum < a.back()) {
        cout << 2 * a.back() << endl;
    } else {
        cout << sum + a.back() << endl;
    }
    return 0;
}
