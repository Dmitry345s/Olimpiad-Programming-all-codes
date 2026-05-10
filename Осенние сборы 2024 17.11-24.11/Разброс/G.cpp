#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const ull p = 1791791791;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<ull> h(n + 1);
    vector<ull> pows(n + 1);
    pows[0] = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        h[i + 1] = (h[i] * p) + a[i];
        pows[i + 1] = (pows[i] * p);
    }
    n--;
    a.pop_back();
    for (int i = 1; i <= n; ++i) {
        if (n % i != 0) continue;
        ull last = 0;
        int flag = 1;
        for (int j = i; j <= n; j += i) {
            if (j == i) {
                last = h[j] - h[j - i] * pows[i];
            } else {
                if (last != h[j] - h[j - i] * pows[i]) {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
