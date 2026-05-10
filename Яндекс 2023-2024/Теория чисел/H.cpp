#include<bits/stdc++.h>

using namespace std;

int MAX = 5e6 + 5;
vector<long long> pr(MAX, 1), pr2(MAX), fget(MAX);

void start() {
    pr[1] = 0;
    for (int i = 2; i * i < MAX; ++i) {
        if (pr[i] == 1) {
            for (int j = 2 * i; j < MAX; j += i) {
                pr[j] = max(pr[j], 1ll * i);
            }
            pr[i] = i;
        }
    }
    pr2[1] = 1;
    fget[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        int cnt = 0, x = i;
        if (pr[i] == 1) {
            pr[i] = i;
        }
        while (x % pr[i] == 0) {
            x /= pr[i];
            cnt += 1;
        }
        long long now = 1;
        for (int j = 0; j <= cnt; ++j) {
            pr2[i] += now * pr2[x];
            now *= pr[i];
        }
        fget[i] = fget[i - 1] + pr2[i];
    }
}

signed main() {
    start();
    int l, r;
    while (cin >> l >> r) {
        long long ans = fget[r] - fget[l - 1];
        cout << ans << endl;
    }
    return 0;
}
