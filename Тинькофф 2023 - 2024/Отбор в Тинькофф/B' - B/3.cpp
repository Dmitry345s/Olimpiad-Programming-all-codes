#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> masks(k);
    for (int i = 0; i < k; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int bit;
            cin >> bit;
            --bit;
            masks[i] += (1 << bit);
        }
    }
    int ans = 0;
    for (int mask = 0; mask < (1 << k); ++mask) {
        int mayans = 0;
        for (int bit = 0; bit < k; ++bit) {
            if ((mask >> bit) & 1) {
                mayans = (mayans ^ masks[bit]);
            }
        }
        if (mayans == (1 << n) - 1) {
            ans = mask;
        }
    }
    if (ans == 0) {
        cout << -1 << endl;
    } else {
        vector<int> rans;
        for (int bit = 0; bit < k; ++bit) {
            if ((ans >> bit) & 1) {
                rans.push_back(bit);
            }
        }
        cout << rans.size() << endl;
        for (int i = 0; i < rans.size(); ++i) {
            cout << rans[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
