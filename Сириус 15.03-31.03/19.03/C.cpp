#include<bits/stdc++.h>

using namespace std;

int MAX = 12e4 + 1;
vector<vector<int>> g(MAX);
vector<int> pr(MAX, -1);
vector<int> used(MAX);

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = 1;
    for (int to : g[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> ls(2 * n), rs(2 * n), ss(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        int l, r, s;
        cin >> l >> r >> s;
        --l; --r;
        ls[i] = l;
        rs[i] = r;
        ss[i] = s;
        g[i].push_back(2 * n + l);
        g[i].push_back(3 * n + r);
        g[3 * n + r].push_back(i);
        g[2 * n + l].push_back(i);
    }
    for (int i = 0; i < (1 << (2 * n)); ++i) {
        int sum1 = 0, sum2 = 0;
        vector<int> mu(n), mu2(n);
        for (int j = 0; j < 2 * n; ++j) {
            if ((i >> j) & 1) {
                sum2 += ss[j];
                mu[ls[j]] += 1;
            } else {
                sum1 += ss[j];
                mu2[rs[j]] += 1;
            }
        }
        int flag = 1;
        for (int i = 0; i < n; ++i) {
            if (mu[i] > 1 || mu2[i] > 1) {
                flag = 0;
                break;
            }
        }
        if (abs(sum1 - sum2) <= k && flag) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
