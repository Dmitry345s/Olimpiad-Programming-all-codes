#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }
    cin >> m;
    vector<vector<int>> now(n);
    vector<vector<int>> now2(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        now[b].push_back(a);
        now2[a].push_back(b);
        if (b > a) {
            cout << -1 << endl;
            return 0;
        }
    }
    vector<int> maxm(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        sort(now2[i].begin(), now2[i].end());
        int cnt = 0;
        for (auto v : now2[i]) {
            //cout << maxm[v] << " " << i << " " << v << endl;
            ans = max(ans, i - v + maxm[v]);
            cnt++;
            maxm[v] = max(maxm[v], cnt);
        }
    }
    cout << ans << endl;
    return 0;
}
