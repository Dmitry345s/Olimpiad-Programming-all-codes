#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e5 + 1, LN = 19;
vector<int> g[MAX];
int tin[MAX], tout[MAX];
int up[LN][MAX];
int h[MAX], sz[MAX];
int timer = 0;

void dfs(int v, int p) {
    up[0][v] = p;
    for (int i = 1; i < LN; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    h[v] = h[p] + 1;
    tin[v] = timer++;
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
    tout[v] = timer;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

int la(int a, int x) {
    for (int i = LN - 1; i >= 0; --i) {
        if ((x >> i) & 1) {
            a = up[i][a];
        }
    }
    return a;
}

bool cmp(int a, int b) {
    return tin[a] < tin[b];
}

vector<int> g2[MAX];
int d[MAX], tp[MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
        d[i] = MAX * 2;
        tp[i] = MAX + 1;
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        vector<int> now(k + 1);
        vector<int> now2(k);
        for (int j = 0; j < k; ++j) {
            cin >> now[j + 1];
            --now[j + 1];
            now2[j] = now[j + 1];
        }
        sort(now.begin(), now.end(), cmp);
        for (int j = 0; j < k; ++j) {
            now.push_back(lca(now[j], now[j + 1]));
        }
        sort(now.begin(), now.end(), cmp);
        now.erase(unique(now.begin(), now.end()), now.end());
        vector<int> st;
        for (int v : now) {
            while (!st.empty() && !ch(st.back(), v)) {
                st.pop_back();
            }
            if (st.empty()) {
                st.push_back(v);
            } else {
                g2[v].push_back(st.back());
                g2[st.back()].push_back(v);
                st.push_back(v);
            }
        }
        set<pair<int, int>> q;
        for (int j = 0; j < k; ++j) {
            d[now2[j]] = 0;
            tp[now2[j]] = j;
            q.insert({d[now2[j]], now2[j]});
        }
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (int to : g2[v]) {
                int c = abs(h[v] - h[to]);
                if (d[to] > d[v] + c) {
                    q.erase({d[to], to});
                    d[to] = d[v] + c;
                    tp[to] = tp[v];
                    q.insert({d[to], to});
                } else if (d[to] == d[v] + c) {
                    tp[to] = min(tp[to], tp[v]);
                }
            }
        }
        int ans = 0;
        for (int v : now) {
            //cout << "! " << v << " " << d[v] << " " << tp[v] << endl;
            if (tp[v] == 0) {
                int now = sz[v];
                for (int to : g2[v]) {
                    int dist = abs(h[v] - h[to]);
                    if (ch(to, v)) {
                        int x = 0;
                        if (d[v] < d[to]) {
                            x += (d[to] - d[v]);
                        }
                        if (x == dist) x -= 1;
                        dist -= abs(d[v] - d[to]);
                        if (dist != 0) {
                            x += dist / 2;
                        }
                        int y = la(v, x);
                        //cout << "# " << x << " ";
                        ans += (sz[y] - sz[v]);
                    } else {
                        int x = 0;
                        if (d[to] < d[v]) {
                            x += (d[v] - d[to]);
                        }
                        if (x == dist) x -= 1;
                        dist -= abs(d[v] - d[to]);
                        if (dist == 0) dist = 1;
                        dist -= 1;
                        x += dist / 2;
                        int y = la(to, x);
                        //cout << x << " ";
                        now -= sz[y];
                    }
                    //cout << to << " ";
                }
                ans += now;
                //cout << endl;
                //cout << v << " " << now << endl;
            }
        }
        cout << ans << endl;
        for (int v : now) {
            g2[v].clear();
            d[v] = 2 * MAX;
            tp[v] = MAX + 1;
        }
    }
    return 0;
}
