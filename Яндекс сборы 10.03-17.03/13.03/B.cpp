#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> ch(n - 1);
    vector<int> ch2(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        ch[i] = (a[i] != a[i + 1]);
        ch2[i] = (a[i] == 2 && a[i + 1] == 1);
    }
    vector<int> pref(n);
    vector<int> pref2(n);
    for (int i = 0; i < n - 1; ++i) {
        pref[i + 1] = pref[i] + ch[i];
        pref2[i + 1] = pref2[i] + ch2[i];
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        int cntall = pref[r - 1] - pref[l] + 1;
        int cnt2 = pref2[r - 1] - pref2[l];
        if (a[r - 1] == 2) {
            cnt2++;
        }
        //cout << cntall << " " << cnt2 << endl;
        int cnt1 = cntall - cnt2;
        if (cnt1 % 2 == 1 && cnt2 % 2 == 1) {
            cout << "Andrey" << endl;
        } else {
            cout << "Timofey" << endl;
        }
    }
    return 0;
}
