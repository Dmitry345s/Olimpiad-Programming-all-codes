#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1, LN = 31;

vector<int> g[MAX];
int usc[MAX];
int num[MAX];
int us[MAX];
vector<int> c;

int fc(int v) {
    us[v] = 1;
    for (int to : g[v]) {
        if (us[to] == 2) continue;
        if (us[to] == 1) {
            c.push_back(v);
            return 1;
        }
        int y = fc(to);
        if (y == 1) {
            c.push_back(v);
            return 1;
        }
    }
    us[v] = 2;
    return 0;
}

int h[MAX], up[MAX][LN];

void dfs(int v, int p) {
    h[v] = h[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p || usc[to] + 1) continue;
        dfs(to, v);
    }
}

int gup(int v, int k) {
    for (int i = LN - 1; i >= 0; --i) {
        if ((k >> i) & 1) {
            v = up[v][i];
        }
    }
    return v;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int p;
    cin >> p;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    fill(usc, usc + n, -1);
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        --s;
        g[s].push_back(i);
    }
    vector<vector<int>> allc;
    for (int i = 0; i < n; ++i) {
        if (!us[i]) {
            c.clear();
            int u = fc(i);
            if (!c.empty()) {
                //reverse(c.begin(), c.end());
                allc.push_back(c);
                for (int i = 0; i < (int)c.size(); ++i) {
                    us[c[i]] = 2;
                    usc[c[i]] = (int)allc.size() - 1;
                    num[c[i]] = i;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (usc[i] != -1) {
            dfs(i, i);
        }
    }
    vector<int> in_end(n);
    for (int i = 0; i < n; ++i) {
        int u = gup(i, k);
        int rup = h[i] - h[u];
        int nk = k - rup;
        if (usc[u] != -1) {
            int y = num[u];
            nk %= (int)allc[usc[u]].size();
            y = (y + nk) % (int)allc[usc[u]].size();
            u = allc[usc[u]][y];
        }
        in_end[u] += a[i];
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) mx = max(in_end[i], mx);
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (in_end[i] == mx) ans.push_back(i);
    }
    cout << mx << endl;
    if (p == 2) {
        for (int v : ans) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
