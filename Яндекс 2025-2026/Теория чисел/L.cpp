#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e8 + 1, MAX2 = 3e7 + 1;
int cnt = 0;
int lp[MAX];
int pr[MAX2];

void solve() {
    lp[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr[cnt] = i;
            cnt++;
        }
        for (int j = 0; j < cnt && pr[j] <= lp[i] && pr[j] * i < MAX; ++j) {
            lp[i * pr[j]] = lp[i];
        }
    }
    for (int i = 2; i < MAX; ++i) {
        if (i / lp[i] % lp[i] == 0) {
            lp[i] *= lp[i / lp[i]];
        } else {
            lp[i] = lp[i / lp[i]] * (lp[i] - 1);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    int n;
    cin >> n;
    vector<long long> to_ans((n + 99) / 100);
    for (int i = 1; i <= n; ++i) {
        to_ans[(i - 1) / 100] += lp[i];
    }
    for (long long v : to_ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
