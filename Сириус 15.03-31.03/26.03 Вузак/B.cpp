#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> cnt(3);
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        int j2 = (j + 1) % n;
        cout << "? " << i + 1 << " " << j + 1 << " " << j + 1 << " " << j2 + 1 << endl;
        char ans;
        cin >> ans;
        if (ans == '0') {
            cout << "! NO" << endl;
            return 0;
        }
        if (ans == '-') {
            cnt[0]++;
        } else {
            cnt[1]++;
        }
    }
    for (int i = 0; i < n - 2; ++i) {
        int j = (i + 1) % n;
        int j2 = (j + 1) % n;
        cout << "? " << 1 << " " << j + 1 << " " << 1 << " " << j2 + 1 << endl;
        char ans;
        cin >> ans;
        if (ans == '0') {
            cout << "! NO" << endl;
            return 0;
        }
        if (ans == '-') {
            cnt[0]++;
        } else {
            cnt[1]++;
        }
    }
    if (cnt[0] && cnt[1]) {
        cout << "! NO" << endl;
        return 0;
    }
    cout << "! YES" << endl;
    return 0;
}
