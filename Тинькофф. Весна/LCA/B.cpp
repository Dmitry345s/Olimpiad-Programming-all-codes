#include<iostream>
#include<vector>

using namespace std;

int lg = 20;
int timer = 0;
void dfs(int v, int p, vector<vector<int>> & g, vector<int> & used, vector<vector<int>> & up, vector<int> & tin, vector<int> & tout) {
    used[v] = 1;
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < lg; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to, v, g, used, up, tin, tout);
        }
    }
    tout[v] = timer++;
}

bool ch(int a, int b, vector<int> & tin, vector<int> & tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b, vector<vector<int>> & up, vector<int> & tin, vector<int> & tout) {
    if (ch(a, b, tin, tout)) {
        return a;
    }
    if (ch(b, a, tin, tout)) {
        return b;
    }
    for (int i = lg - 1; i >= 0; --i) {
        if (!ch(up[a][i], b, tin, tout)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    int n;
    cin >> n;
    while (n) {
        timer = 0;
        vector<vector<int>> up(n, vector<int> (lg));
        vector<vector<int>> g(n);
        vector<int> used(n), tin(n), tout(n);
        for (int i = 0; i < n - 1; ++i) {
            int v, to;
            cin >> v >> to;
            --v; --to;
            g[v].push_back(to);
            g[to].push_back(v);
        }
        dfs(0, 0, g, used, up, tin, tout);
        int r = 0;
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            char p;
            cin >> p;
            if (p == '!') {
                int nr;
                cin >> nr;
                --nr;
                r = nr;
            } else {
                int a, b;
                cin >> a >> b;
                --a; --b;
                cout << (lca(a, b, up, tin, tout) ^ lca(r, b, up, tin, tout) ^ lca(r, a, up, tin, tout)) + 1 << endl;
            }
        }
        cin >> n;
    }
    return 0;
}
