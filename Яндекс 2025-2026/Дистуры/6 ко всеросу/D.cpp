#include<bits/stdc++.h>

using namespace std;

const int MAX = 1000;

vector<int> g[MAX];

pair<int, int> get(int n) {
    int mx = 0;
    pair<int, int> ans = {0, 0};
    for (int st : g[0]) {
        vector<int> d(n, n + 1);
        queue<int> q;
        q.push(st);
        d[st] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (d[to] > d[v] + 1) {
                    q.push(to);
                    d[to] = d[v] + 1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (d[i] > mx) {
                ans = {st, i};
                mx = d[i];
            }
        }
    }
    return ans;
}

signed main() {
    freopen("2in.txt", "r", stdin);
    freopen("02.txt", "w", stdout);
    int n, k, w;
    cin >> n >> k >> w;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    g[0].push_back(0);
    if (k == -1) {
        for (int i = 10; i <= n; i += 10) {
            cout << 1 << " " << i << endl;
        }
    } else if (k == -1) {
        for (int i = 4; i <= 901; i += 3) {
            cout << 1 << " " << i << endl;
        }
    } else {
        for (int u = 0; u < k; ++u) {
            pair<int, int> gt = get(n);
            cout << gt.first + 1 << " " << gt.second + 1 << endl;
            g[gt.first].push_back(gt.second);
            g[gt.second].push_back(gt.first);
        }
    }
    return 0;
}
