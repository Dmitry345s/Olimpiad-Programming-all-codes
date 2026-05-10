#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    int x = b[n / 2];
    if (b[n / 2] != b[n / 2 - 1]) {
        cout << "No" << endl;
        return 0;
    }
    vector<int> pref1(n + 1), pref2(n + 1);
    for (int i = 0; i < n; ++i) {
        pref1[i + 1] = pref1[i];
        pref2[i + 1] = pref2[i];
        if (a[i] < x) {
            pref1[i + 1]++;
        } else if (a[i] == x) {
            pref2[i + 1]++;
        }
    }
    vector<int> suf1(n + 1), suf2(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        suf1[i] = suf1[i + 1];
        suf2[i] = suf2[i + 1];
        if (a[i] < x) {
            suf1[i]++;
        } else if (a[i] == x) {
            suf2[i]++;
        }
    }
    int fl = 0;
    for (int i = 1; i < n; i += 2) {
        if (pref1[i] <= i / 2 && pref1[i] + pref2[i] > i / 2 && suf1[i] <= (n - i) / 2 && suf1[i] + suf2[i] > (n - i) / 2) {
            fl = 1;
        }
    }
    if (fl) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
