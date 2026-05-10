#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 3e5 + 1;
vector<int> g[MAX];
int ch[MAX], del[MAX], nx[MAX], num[MAX];
const int INF = 2e18;

int chh(int v, int time) {
    if (del[v] == -1 || time < ch[v] || (time - ch[v]) % del[v] != 0) return 0;
    return 1;
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
        ch[i] = -1;
        del[i] = -1;
        num[i] = -1;
        nx[i] = INF;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l;
        cin >> l;
        vector<int> now;
        for (int j = 0; j < l; ++j) {
            int v;
            cin >> v;
            --v;
            now.push_back(v);
            ch[v] = j;
            del[v] = l;
            num[v] = i;
        }
        int last = -1;
        for (int j = l - 1; j >= 0; --j) {
            if ((int)g[now[j]].size() > 2) {
                last = j;
            }
            if (last != -1) {
                nx[now[j]] = last - j;
            } else {
                nx[now[j]] = -1;
            }
        }
        int dist = last;
        int j = l - 1;
        while (j >= 0 && nx[now[j]] == -1) {
            nx[now[j]] = dist + l - j;
            --j;
        }
    }
    vector<int> d(n, INF);
    d[0] = 0;
    set<pair<int, int>> q;
    q.insert({0, 0});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        int t = d[v];
        for (int to : g[v]) {
            int now = chh(to, t);
            int nxv = chh(v, t + 1);
            int nxto = chh(to, t + 1);
            int cs = 1;
            if (now && nxv) {
                cs = min(del[v] - 1, (nx[v] + 1) * 2 + 1);
            } else if (nxto) {
                if (num[v] != num[to]) {
                    cs = 2;
                } else {
                    cs = min(del[v] - 1, (nx[v] + 1) * 2 + 1 + 1);
                }
            }
            if (t + cs < d[to]) {
                q.erase({d[to], to});
                d[to] = t + cs;
                q.insert({d[to], to});
            }
        }
    }
    if (d[n - 1] == INF) {
        cout << "impossible" << endl;
    } else {
        cout << d[n - 1] << endl;
    }
    return 0;
}

