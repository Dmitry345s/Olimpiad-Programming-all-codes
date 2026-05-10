#include<bits/stdc++.h>

using namespace std;

const int MAX = 1001;
const int INF = MAX * MAX * MAX;

vector<int> g[MAX];
int dist[MAX][MAX];
int dp[MAX][MAX];
pair<int, int> p[MAX][MAX];

signed main() {
    int n, m;
    cin >> n >> m;
    int s1, e1, s2, e2;
    cin >> s1 >> e1 >> s2 >> e2;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int st = 0; st < n; ++st) {
        for (int i = 0; i < n; ++i) {
            dist[st][i] = INF;
        }
        queue<int> q;
        dist[st][st] = 0;
        q.push(st);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (dist[st][to] == INF) {
                    dist[st][to] = dist[st][v] + 1;
                    q.push(to);
                }
            }
        }
    }
    //cout << -1 << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = -1;
            p[i][j] = {-1, -1};
        }
    }
    set<array<int, 3>> q;
    dp[s1][s2] = dist[s1][s2];
    q.insert({-dp[s1][s2], s1, s2});
    while (!q.empty()) {
        auto [dpn, n1, n2] = *q.begin();
        //cout << n1 << " " << n2 << endl;
        q.erase(q.begin());
        for (int to : g[n1]) {
            if (min(dp[n1][n2], dist[to][n2]) > dp[to][n2]) {
                q.erase({-dp[to][n2], to, n2});
                dp[to][n2] = min(dp[n1][n2], dist[to][n2]);
                p[to][n2] = {1, n1};
                q.insert({-dp[to][n2], to, n2});
            }
        }
        for (int to : g[n2]) {
            if (min(dp[n1][n2], dist[n1][to]) > dp[n1][to]) {
                q.erase({-dp[n1][to], n1, to});
                dp[n1][to] = min(dp[n1][n2], dist[n1][to]);
                p[n1][to] = {2, n2};
                q.insert({-dp[n1][to], n1, to});
            }
        }
    }
    int d = dp[e1][e2];
    vector<pair<int, int>> ans;
    //cout << p[0][7].first << " " << p[0][7].second << endl;
    while (p[e1][e2] != pair<int, int>{-1, -1}) {
        //cout << e1 << " " << e2 << endl;
        ans.push_back({e1, e2});
        if (p[e1][e2].first == 1) {
            e1 = p[e1][e2].second;
        } else {
            e2 = p[e1][e2].second;
        }
    }
    ans.push_back({s1, s2});
    reverse(ans.begin(), ans.end());
    cout << (int)ans.size() - 1 << endl;
    for (int i = 0; i < (int)ans.size() - 1; ++i) {
        if (ans[i].first != ans[i + 1].first) {
            cout << 1 << " " << ans[i + 1].first << endl;
        } else {
            cout << 2 << " " << ans[i + 1].second << endl;
        }
    }
    cout << d << endl;
    return 0;
}
