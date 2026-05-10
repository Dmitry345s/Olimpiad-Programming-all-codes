#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int MAX = 1e8 + 1, MAX2 = 2e7 + 1, MAX3 = 100;
int cnt = 0;
int lp[MAX];
int pr[MAX2];

void solve() {
    lp[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            pr[cnt] = i;
            cnt++;
        }
        int u = pr[0] * i;
        int tt = abs(lp[i]);
        int j = 0;
        for (; pr[j] < tt && u < MAX; ++j) {
            lp[u] = pr[j];
            u = pr[j + 1] * i;
        }
        if (u < MAX) {
            lp[u] = -pr[j];
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
    to_ans[0] = 1;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] < 0) {
            lp[i] *= -lp[i / abs(lp[i])];
        } else {
            lp[i] = lp[i / abs(lp[i])] * (lp[i] - 1);
        }
        to_ans[(i - 1) / 100] += lp[i];
    }
    for (long long v : to_ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
