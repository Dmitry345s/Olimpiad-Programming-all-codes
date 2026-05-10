#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(2 * n + 2);
    for (int i = 0; i < 2 * n + 2; ++i) {
        cin >> a[i];
    }
    vector<int> ans(n);
    ans[0] = 0;
    for (int i = 3; i < 2 * n; i += 2) {
        //cout << i << " " << i / 2 << " " << i / 2 - 1 << endl;
        if (a[i] == 1) {
            ans[i / 2] = (ans[i / 2 - 1] ^ 1);
        } else {
            ans[i / 2] = ans[i / 2 - 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (char)(ans[i] + 97);
    }
    cout << endl;
    return 0;
}
