#include<bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;

const int MAX = 5e4 + 5, INF = 1e18;

vector<int> g[MAX];
int s[MAX];

void bfs(int st, vector<int> & d) {
    queue<int> q;
    d[st] = 0;
    q.push(st);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[to] > d[v] + 1) {
                if (s[to] == 0) {
                    q.push(to);
                }
                d[to] = d[v] + 1;
            }
        }
    }
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        s[i] = c - '0';
        cnt += s[i];
    }
    vector<int> x(k);
    for (int i = 0; i < k; ++i) {
        cin >> x[i];
        --x[i];
    }
    if (cnt == 0) {
        vector<int> d(n, INF);
        bfs(x[0], d);
        for (int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << endl;
        return 0;
    }
    if (cnt == 1) {
        vector<int> d2(n, INF);
        int in = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i]) {
                bfs(i, d2);
                in = i;
            }
        }
        vector<int> d1(n, INF);
        bfs(x[0], d1);
        int add = 0;
        for (int i = 1; i < k; ++i) {
            add += d2[x[i]];
            if (x[i] == in) {
                add += 2;
            }
        }
        vector<int> d(n, INF);
        for (int i = 0; i < n; ++i) {
            d[i] = min(d1[i], d1[in] + add + d2[i]);
        }
        for (int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << endl;
        return 0;
    }
    if (cnt == 2) {
        int in1 = -1;
        int in2 = -1;
        vector<int> d2(n, INF);
        vector<int> d3(n, INF);
        for (int i = 0; i < n; ++i) {
            if (s[i] && in1 == -1) {
                bfs(i, d2);
                in1 = i;
            } else if (s[i]) {
                bfs(i, d3);
                in2 = i;
            }
        }
        vector<int> d1(n, INF);
        bfs(x[0], d1);
        vector<int> d(n, INF);
        int add = 0;
        for (int i = 1; i < k; ++i) {
            int v = x[i];
            add += min(d2[v] + 2 * (v == in1), d3[v] + 2 * (v == in2));
        }
        int add2 = 0;
        if (d2[in2] == 1) {
            add2 += k - 1;
        } else {
            add2 += 2 * k - 2;
        }
        for (int i = 0; i < n; ++i) {
            d[i] = min(d[i], d1[i]);
            d[i] = min(d[i], d1[in1] + add + d2[i]);
            d[i] = min(d[i], d1[in2] + add + d3[i]);
            d[i] = min(d[i], d1[in1] + d2[in2] + add + add2 + d3[i]);
            d[i] = min(d[i], d1[in2] + d3[in1] + add + add2 + d2[i]);
        }
        for (int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << endl;
        return 0;
    }
    return 0;
}
