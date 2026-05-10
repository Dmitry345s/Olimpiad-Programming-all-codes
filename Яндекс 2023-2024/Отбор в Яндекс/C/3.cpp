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
    vector<int> b(n);
    for (int i = 0; i < (n + 1) / 2; ++i) {
        b[i * 2] = a[i];
    }
    for (int i = (n + 1) / 2; i < n; ++i) {
        int j = i - (n + 1) / 2;
        b[2 * j + 1] = a[i];
    }
    string ans = "Yes";
    for (int i = 1; i < n; i += 2) {
        if (!(b[i] > b[i - 1] && b[i] > b[i + 1])) {
            ans = "No";
            break;
        }
    }
    cout << ans << endl;
    return 0;
}

