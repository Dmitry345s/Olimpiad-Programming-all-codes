#include<bits/stdc++.h>

using namespace std;

int MAX = 10000 + 1;
vector<vector<int>> g(MAX);
vector<int> used(MAX), pr(MAX, -1);

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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<string> vc(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> vc[i];
        for (int j = 0; j < m; ++j) {
            if (vc[i][j] == '*') cnt++;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i % 2; j < m; j += 2) {
            if (vc[i][j] == '.') continue;
            if (j + 1 < m && vc[i][j + 1] == '*') {
                g[(i * m + j) / 2].push_back((i * m + j + 1) / 2);
            }
            if (j - 1 >= 0 && vc[i][j - 1] == '*') {
                g[(i * m + j) / 2].push_back((i * m + j - 1) / 2);
            }
            if (i + 1 < n && vc[i + 1][j] == '*') {
                g[(i * m + j) / 2].push_back((i * m + m + j) / 2);
            }
            if (i - 1 >= 0 && vc[i - 1][j] == '*') {
                g[(i * m + j) / 2].push_back((i * m - m + j) / 2);
            }
        }
    }
    for (int i = 0; i < (n * m + 1) / 2; ++i) {
        used.assign((n * m + 1) / 2, 0);
        try_kuhn(i);
    }
    int cnt2 = 0;
    for (int i = 0; i < (n * m + 1) / 2; ++i) {
        if (pr[i] != -1) {
            cnt2++;
        }
    }
    cout << min((long long)cnt * b, (cnt - 2 * cnt2) * (long long)b + cnt2 * (long long)a) << endl;
}
