#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1, INF = 1e9;
vector<int> g[MAX];
int d[MAX][2];
int p[MAX][2];

void bfs() {
    d[0][0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[v][0] + 1 < d[to][1]) {
                d[to][1] = d[v][0] + 1;
                p[to][1] = v;
                q.push(to);
            }
            if (d[v][1] + 1 < d[to][0]) {
                d[to][0] = d[v][1] + 1;
                p[to][0] = v;
                q.push(to);
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        d[i][0] = INF;
        d[i][1] = INF;
        p[i][0] = -1;
        p[i][1] = -1;
    }
    bfs();
    int now = n - 1, now2 = (d[n - 1][0] == INF);
    vector<int> ans;
    while (p[now][now2] != -1) {
        ans.push_back(p[now][now2]);
        now = p[now][now2];
        now2 ^= 1;
    }
    reverse(ans.begin(), ans.end());
    cout << (d[n - 1][0] == INF) << " " << (int)ans.size() + 1 << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
        if (i % 2) {
            cout << "- ";
        } else {
            cout << "+ ";
        }
    }
    cout << n << endl;
    return 0;
}
