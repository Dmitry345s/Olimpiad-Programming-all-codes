#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 505;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int allsum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        allsum += a[i];
    }
    bitset<MAX * MAX> ans;
    for (int i = 0; i < MAX * MAX; ++i) {
        ans[i] = 1;
    }
    vector<bitset<MAX * MAX>> pref(n + 1);
    vector<bitset<MAX * MAX>> suf(n + 1);
    pref[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = (pref[i] | (pref[i] << a[i]));
    }
    suf[n][0] = 1;
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = (suf[i + 1] | (suf[i + 1] << a[i]));
    }
    if (allsum % 2 || !pref.back()[allsum / 2]) {
        cout << 0 << endl;
        return 0;
    }
    bitset<MAX * MAX> now;
    for (int i = 0; i < n; ++i) {
        int sum = allsum - a[i];
        if (i > n / 2) {
            now = pref[i];
            for (int j = i + 1; j < n; ++j) {
                now |= (now << a[j]);
            }
        } else {
            now = suf[i + 1];
            for (int j = 0; j < i; ++j) {
                now |= (now << a[j]);
            }
        }
        bitset<MAX * MAX> tans;
        for (int j = 0; j < MAX * MAX; ++j) {
            if (abs(2 * j - sum) >= MAX * MAX) break;
            tans[abs(2 * j - sum)] = (tans[abs(2 * j - sum)] | now[j]);
        }
        ans &= tans;
    }
    vector<int> rans;
    for (int i = 1; i < MAX * MAX; ++i) {
        if (ans[i]) {
            rans.push_back(i);
        }
    }
    cout << (int)rans.size() << endl;
    //assert((int)rans.size() < MAX);
    for (int v : rans) {
        //assert(abs(allsum - v) < 4 * MAX || v < 2 * MAX);
        cout << v << " ";
    }
    cout << endl;
    return 0;
}

