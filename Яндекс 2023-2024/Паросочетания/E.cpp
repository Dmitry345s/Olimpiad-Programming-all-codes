#include<bits/stdc++.h>

using namespace std;

int MAX = 300 + 1;
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
    int n;
    cin >> n;
    vector<set<string>> a(n);
    for (int i = 0; i < n; ++i) {
        int j;
        cin >> j;
        for (int k = 0; k < j; ++k) {
            string ch;
            cin >> ch;
            a[i].insert(ch);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            int flag = 1;
            for (auto st : a[i]) {
                if (a[j].find(st) == a[j].end()) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                g[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        used.assign(n, 0);
        try_kuhn(i);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (pr[i] == -1) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
