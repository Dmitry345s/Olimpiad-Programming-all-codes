#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5 + 1;
vector<vector<int>> g(MAX);
vector<int> used(MAX), pr(MAX, -1), pr2(MAX, -1);

bool try_kuhn(int v, int num) {
    if (used[v] == num) return false;
    used[v] = num;
    for (int to : g[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to], num)) {
            pr[to] = v;
            pr2[v] = to;
            return true;
        }
    }
    return false;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a;
            cin >> a;
            --a;
            g[a].push_back(i);
        }
    }
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long ans = 0;
    vector<long long> b(n);
    vector<pair<int, int>> ch;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        ch.push_back({a[i] - b[i], i});
        ans += b[i];
    }
    sort(ch.begin(), ch.end());
    for (int i = 0; i < n; ++i) {
        if (pr2[ch[i].second] != -1) continue;
        try_kuhn(ch[i].second, i + 1);
    }
    vector<vector<int>> rans;
    for (int i = 0; i < n; ++i) {
        if (pr[i] == -1) {
            rans.push_back({});
            int to = i;
            while (pr2[to] != -1) {
                rans.back().push_back(to);
                to = pr2[to];
            }
            rans.back().push_back(to);
            ans -= b[to] - a[to];
            reverse(rans.back().begin(), rans.back().end());
        }
    }
    cout << ans << " " << rans.size() << endl;
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i].size() << " ";
        for (int j = 0; j < (int)rans[i].size(); ++j) {
            cout << rans[i][j] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
