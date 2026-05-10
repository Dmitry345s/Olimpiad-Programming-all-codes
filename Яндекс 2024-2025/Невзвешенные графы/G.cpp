#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e5 + 1;
vector<int> g[MAX];
vector<int> gt[MAX];
vector<int> gn[MAX];
vector<int> gnt[MAX];
int used[MAX], ch[MAX];
vector<int> top_sort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    top_sort.push_back(v);
}

int used2[MAX];
vector<int> cmps[MAX + 1];

void dfs2(int v, int num) {
    used2[v] = num;
    cmps[num].push_back(v);
    for (int to : gt[v]) {
        if (!used2[to]) {
            dfs2(to, num);
        }
    }
}

int used3[MAX];

void dfs3(int v) {
    used3[v]++;
    for (int to : gn[v]) {
        if (used3[to] == 0) {
            dfs3(to);
        }
    }
}

void dfs4(int v) {
    used3[v]++;
    for (int to : gnt[v]) {
        if (used3[to] == 1) {
            dfs4(to);
        }
    }
}

int used4[MAX];
int tin[MAX], fup[MAX], is[MAX];
int timer = 0;

void dfs5(int v, int p) {
    used4[v] = 1;
    tin[v] = timer++;
    fup[v] = tin[v];
    int ch = 0;
    for (int to : gn[v]) {
        if (used3[to] != 2) continue;
        if (!used4[to]) {
            dfs5(to, v);
            ch++;
            fup[v] = min(fup[v], fup[to]);
            if (v != p && fup[to] >= tin[v]) {
                is[v] = 1;
            }
        } else {
            fup[v] = min(fup[v], tin[to]);
        }
    }
    for (int to : gnt[v]) {
        if (used3[to] != 2) continue;
        if (!used4[to]) {
            dfs5(to, v);
            ch++;
            fup[v] = min(fup[v], fup[to]);
            if (v != p && fup[to] >= tin[v]) {
                is[v] = 1;
            }
        } else {
            fup[v] = min(fup[v], tin[to]);
        }
    }
    if (v == p && ch > 1) {
        is[v] = 1;
    }
}

bool cmp(int a, int b) {
    if (tin[used2[a]] == tin[used2[b]]) return a < b;
    return tin[used2[a]] < tin[used2[b]];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i <= n; ++i) {
            g[i].clear();
            gt[i].clear();
            gn[i].clear();
            gnt[i].clear();
            used[i] = 0;
            ch[i] = 0;
            used2[i] = 0;
            used3[i] = 0;
            is[i] = 0;
            tin[i] = 0;
            used4[i] = 0;
            fup[i] = 0;
            cmps[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if (a == b) {
                ch[a] = 1;
            } else {
                g[a].push_back(b);
                gt[b].push_back(a);
            }
        }
        top_sort.clear();
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
        reverse(top_sort.begin(), top_sort.end());
        int num = 0;
        for (int v : top_sort) {
            if (!used2[v]) {
                num++;
                dfs2(v, num);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int to : g[i]) {
                if (used2[to] != used2[i]) {
                    gn[used2[i]].push_back(used2[to]);
                }
            }
        }
        for (int i = 0; i < n + 1; ++i) {
            sort(gn[i].begin(), gn[i].end());
            gn[i].erase(unique(gn[i].begin(), gn[i].end()), gn[i].end());
            for (int to : gn[i]) {
                gnt[to].push_back(i);
            }
        }
        dfs3(used2[0]);
        dfs4(used2[n - 1]);
        timer = 0;
        dfs5(used2[0], used2[0]);
        vector<int> ans;
        is[used2[0]] = 1;
        is[used2[n - 1]] = 1;
        for (int v = 0; v <= n; ++v) {
            if (is[v] && (int)cmps[v].size() == 1 && !ch[cmps[v][0]] && used3[v] == 2) {
                ans.push_back(cmps[v][0]);
            }
        }
        sort(ans.begin(), ans.end(), cmp);
        cout << (int)ans.size() << endl;
        for (int v : ans) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
