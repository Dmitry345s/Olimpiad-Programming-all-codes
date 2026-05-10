#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;
vector<int> g[MAX], gt[MAX];
set<int> all[MAX], allt[MAX];
int bd[MAX];
int p[MAX];

int root(int v) {
    if (v == p[v]) return v;
    return p[v] = root(p[v]);
}

void unite(int v, int u) {
    if (root(v) == root(u)) return;
    int rv = root(v);
    int ru = root(u);
    p[rv] = ru;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        all[a].insert(b);
        allt[b].insert(a);
        cnt[a]++;
    }
    queue<int> qq;
    for (int i = 0; i < n; ++i) {
        if ((int)all[i].size() == 0) {
            qq.push(i);
        }
        p[i] = i;
    }
    while (!qq.empty()) {
        int v = qq.front();
        qq.pop();
        bd[v] = 1;
        for (int to : allt[v]) {
            all[to].erase(v);
            if ((int)all[to].size() == 0) {
                qq.push(to);
            }
        }
        allt[v].clear();
    }
    vector<int> us(n);
    for (int i = 0; i < n; ++i) {
        if ((int)all[i].size() == 1) {
            qq.push(i);
            us[i] = 1;
        }
    }
    while (!qq.empty()) {
        int v = qq.front();
        qq.pop();
        if ((int)all[v].size() == 0) continue;
        us[v] = 0;
        int u = *all[v].begin();
        unite(v, u);
        all[v].clear();
        allt[u].erase(v);
        if ((int)allt[v].size() < (int)allt[u].size() + (int)all[u].size()) {
            for (int to : allt[v]) {
                all[to].erase(v);
                all[to].insert(u);
                allt[u].insert(to);
                if ((int)all[to].size() == 1 && !us[to]) {
                    qq.push(to);
                    us[to] = 1;
                }
            }
            allt[v].clear();
        } else {
            set<int> tt = allt[u], t = all[u];
            all[u].clear();
            allt[u].clear();
            for (int to : tt) {
                all[to].erase(u);
                all[to].insert(v);
                allt[v].insert(to);
                if ((int)all[to].size() == 1 && !us[to]) {
                    qq.push(to);
                    us[to] = 1;
                }
            }
            for (int to : t) {
                allt[to].erase(u);
                all[v].insert(to);
                allt[to].insert(v);
            }
            if ((int)all[v].size() == 1 && !us[v]) {
                qq.push(v);
                us[v] = 1;
            }
            all[u].clear();
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (bd[a] || bd[b] || root(a) == root(b)) {
            cout << "King Zhou" << endl;
        } else {
            cout << "Copernicus" << endl;
        }
    }
    return 0;
}
/*
8 12
1 2
2 3
3 1
1 3
2 1
3 2
4 1
5 4
6 5
7 5
8 6
8 7
100
8 4
*/
