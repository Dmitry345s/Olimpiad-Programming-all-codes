#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e8 + 1;
int lp[MAX];
long long ans[(MAX + 99) / 100];
vector<int> pr;

void sieve() {
    for (int i = 2; i < MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && pr[j] * i < MAX; ++j) {
            lp[pr[j] * i] = pr[j];
        }
    }
}

signed main() {
    int n;
    cin >> n;
    sieve();
    //cout << 0 << endl;
    ans[0] = 1;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == i) {
            lp[i] = -(i - 1);
            ans[(i - 1) / 100] += -lp[i];
            continue;
        }
        int x2 = i / lp[i];
        if (x2 % lp[i] == 0) {
            lp[i] = lp[x2] * lp[i];
        } else {
            lp[i] = lp[x2] * (lp[i] - 1);
        }
        ans[(i - 1) / 100] += -lp[i];
    }
    for (int i = 0; i < (n + 98) / 100; ++i) {
        cout << ans[i] << '\n';
    }
}
