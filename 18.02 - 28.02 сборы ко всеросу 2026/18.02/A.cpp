#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            g[v].push_back(i);
        }
    }
    int rans = INF;
    for (int st = 0; st < n; ++st) {
        vector<int> ch(n);
        vector<int> d(n, INF);
        d[st] = 1;
        ch[st] = 1;
        queue<int> q;
        q.push(st);
        int ans = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (!ch[to]) {
                    d[to] = d[v] + 1;
                    q.push(to);
                    ch[to] = 1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!ch[i]) {
                ans = INF;
                break;
            }
            ans += d[i];
        }
        //cout << st << " " << ans << endl;
        rans = min(rans, ans);
    }
    cout << rans << endl;
    return 0;
}
