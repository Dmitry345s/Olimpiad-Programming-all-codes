#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

#define int long long

using namespace std;

const int MAX = 3e6 + 5;
int cnt[MAX];
int pref[MAX + 1];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int now;
        cin >> now;
        cnt[now]++;
    }
    for (int i = 0; i < MAX; ++i) {
        pref[i + 1] = pref[i] + cnt[i];
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < MAX; j += i) {
            int ncnt = pref[j + i] - pref[j];
            if (ncnt == 0) {
                cout << j / i << " ";
                break;
            }
        }
    }
    cout << endl;
    return 0;
}
