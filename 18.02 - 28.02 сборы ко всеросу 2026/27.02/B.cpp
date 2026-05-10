#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 10001;
int used[MAX];
vector<int> g[MAX];
vector<int> now;
vector<int> now2;
const int LN = 60;
const int INF = 2 * MAX;

void dfs(int v) {
    used[v] = 1;
    now.push_back(v);
    now2.push_back(v);
    if ((int)now.size() >= LN) return;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
        if ((int)now.size() >= LN) return;
        now2.push_back(v);
    }
}

mt19937 rnd(57);

signed main() {
    int _;
    cin >> _;
    string s;
    cin >> s;
    if (s == "Alice") {
        int n, m, x;
        cin >> n >> m >> x;
        vector<pair<int, int>> uuu;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            //if (u > v) swap(u, v);
            uuu.push_back({u, v});
        }
        sort(uuu.begin(), uuu.end());
        for (auto [u, v] : uuu) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int cnt = 0;
        vector<int> ans(n);
        vector<int> tr(n);
        for (int i = 0; i < n; ++i) tr[i] = i;
        shuffle(tr.begin(), tr.end(), rnd);
        for (int i : tr) {
            if (!used[i]) {
                now.clear();
                now2.clear();
                dfs(i);
                if ((int)now.size() < LN) {
                    for (int v : now) {
                        ans[v] = 0;
                    }
                } else {
                    for (int i = 0; i < (int)now.size(); ++i) {
                        ans[now[i]] = ((x >> i) & 1);
                    }
                    cnt++;
                }
            }
        }
        assert(cnt > 0);
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << " ";
        }
        cout << endl;
    } else {
        int n, m, w, r;
        cin >> n >> m >> w >> r;
        vector<int> ans(n, -1);
        vector<pair<int, int>> uuu;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            //if (u > v) swap(u, v);
            uuu.push_back({u, v});
        }
        sort(uuu.begin(), uuu.end());
        for (auto [u, v] : uuu) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<vector<int>> all;
        vector<int> num(n);
        vector<int> num2(n);
        vector<int> tr(n);
        for (int i = 0; i < n; ++i) tr[i] = i;
        shuffle(tr.begin(), tr.end(), rnd);
        for (int i : tr) {
            if (!used[i]) {
                now.clear();
                now2.clear();
                dfs(i);
                all.push_back(now2);
                int cnt = 0;
                for (int v : now2) {
                    num[v] = (int)all.size() - 1;
                    num2[v] = cnt;
                    cnt++;
                }
                if ((int)now.size() < LN) {
                    for (int v : now) {
                        ans[v] = -1;
                    }
                } else {
                    for (int i = 0; i < (int)now.size(); ++i) {
                        ans[now[i]] = i;
                    }
                }
            }
        }
        vector<int> dist(n, INF);
        vector<int> p(n, -1);
        dist[w] = 0;
        queue<int> q;
        q.push(w);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (dist[to] == INF) {
                    p[to] = v;
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        int mn1 = INF;
        int in1 = -1;
        for (int i = 0; i < n; ++i) {
            if (ans[i] != -1 && dist[i] + (int)all[num[i]].size() + min(num2[i], (int)all[num[i]].size() - num2[i] - 1) < mn1) {
                mn1 = dist[i] + (int)all[num[i]].size() + min(num2[i], (int)all[num[i]].size() - num2[i] - 1);
                in1 = i;
            }
        }
        //assert(mn1 <= 125);
        if (1) {
            vector<int> ver;
            ver.push_back(in1);
            int ws = in1;
            while (p[in1] != -1) {
                ver.push_back(p[in1]);
                in1 = p[in1];
            }
            reverse(ver.begin(), ver.end());
            assert(ver[0] == w);
            if (num2[ws] > (int)all[num[ws]].size() - num2[ws] - 1) {
                for (int i = num2[ws] + 1; i < (int)all[num[ws]].size(); ++i) {
                    ver.push_back(all[num[ws]][i]);
                }
                for (int i = (int)all[num[ws]].size() - 2; i >= 0; --i) {
                    ver.push_back(all[num[ws]][i]);
                }
            } else {
                for (int i = num2[ws] - 1; i >= 0; --i) {
                    ver.push_back(all[num[ws]][i]);
                }
                for (int i = 1; i < (int)all[num[ws]].size(); ++i) {
                    ver.push_back(all[num[ws]][i]);
                }
            }
            vector<int> tans;
            tans.push_back(r);
            vector<int> cnt(LN);
            assert((int)ver.size() <= 20000);
            assert((int)ver.size() >= 60);
            int ch = 0;
            if (ans[w] != -1) {
                ch = 1;
                cnt[ans[w]] = 1;
            }
            int u = (int)ver.size();
            for (int i = 1; i < (int)ver.size(); ++i) {
                cout << "Move " << ver[i] << endl;
                int tp;
                cin >> tp;
                tans.push_back(tp);
                if (ans[ver[i]] != -1) {
                    if (!cnt[ans[ver[i]]]) {
                        cnt[ans[ver[i]]] = 1;
                        ch++;
                    }
                }
                if (ch == LN) {
                    u = i + 1;
                    break;
                }
            }
            int nx = 0;
            for (int i = 0; i < u; ++i) {
                if (ans[ver[i]] == -1) continue;
                nx |= (tans[i] << ans[ver[i]]);
            }
            cout << "Ready " << nx << endl;
        }
    }
    return 0;
}
