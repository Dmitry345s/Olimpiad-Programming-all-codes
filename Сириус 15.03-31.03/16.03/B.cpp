#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5 + 3;
vector<vector<int>> g(MAX);
vector<set<int>> g2(MAX);
vector<int> cl(MAX), used(MAX), used2(MAX);
int k;
int flag = 1;
vector<int> news;

void dfs(int v, int p) {
    if (k - (int)g2[v].size() == 1) {
        used[v] = 1;
        for (int cl2 = 1; cl2 <= k; ++cl2) {
            if (g2[v].find(cl2) == g2[v].end()) {
                cl[v] = cl2;
                break;
            }
        }
        for (int to : g[v]) {
            if (cl[to] == -1) {
                g2[to].insert(cl[v]);
            }
        }
        for (int to : g[v]) {
            if (to == p) continue;
            if (cl[to] == -1) {
                dfs(to, v);
            }
        }
    }
    //cout << v << " " << cl[v] << endl;
}

void dfs2(int v, int p) {
    used[v] = 1;
    for (int cl2 = 1; cl2 <= k; ++cl2) {
        if (g2[v].find(cl2) == g2[v].end()) {
            cl[v] = cl2;
            break;
        }
    }
    if (cl[v] == -1) {
        flag = 0;
        return;
    }
    for (int to : g[v]) {
        if (cl[to] == -1) {
            g2[to].insert(cl[v]);
        }
    }
    for (int to : g[v]) {
        if (to == p) continue;
        if (cl[to] == -1) {
            dfs(to, v);
        }
    }
}
signed main() {
    int n, m;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> cl[i];
        if (cl[i] != -1) {
            used2[i] = 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        if (cl[b] != -1 && cl[a] == -1) {
            g2[a].insert(cl[b]);
        }
        g[b].push_back(a);
        if (cl[a] != -1 && cl[b] == -1) {
            g2[b].insert(cl[a]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (cl[i] != -1) continue;
        if (used[i]) continue;
        if (k - (int)g2[i].size() == 1) {
            dfs(i, i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (cl[i] != -1) continue;
        if (used[i]) continue;
        flag = 1;
        dfs2(i, i);
        if (flag == 0) {
            cout << "No" << endl;
            return 0;
        }

    }
    flag = 1;
    for (int i = 0; i < n; ++i) {
        if (cl[i] == -1) {
            flag = 0;
        }
        for (int to : g[i]) {
            if (cl[to] == cl[i]) {
                flag = 0;
            }
        }
    }
    if (flag == 0) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for (int i = 0; i < n; ++i) {
            cout << cl[i] << " ";
        }
    }
    return 0;
}
