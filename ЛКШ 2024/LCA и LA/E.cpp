#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 3, LN = 19;
vector<int> p(MAX), h(MAX);
vector<vector<int>> up(MAX, vector<int> (LN));

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

void unite(int v, int u) {
    p[u] = v;
}

int lca(int a, int b) {
    if (h[a] < h[b]) {
        swap(a, b);
    }
    //cout << a << " " << b << " " << h[a] << " " << h[b] << endl;
    for (int i = LN - 1; i >= 0; --i) {
        if (h[up[a][i]] >= h[b]) {
            a = up[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LN - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

signed main() {
    int m;
    cin >> m;
    int now = 1;
    for (int i = 0; i < MAX; ++i) {
        p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int v;
            cin >> v;
            v--;
            h[now] = h[v] + 1;
            //cout << now << " " << h[now] << endl;
            up[now][0] = v;
            for (int j = 1; j < LN; ++j) {
                up[now][j] = up[up[now][j - 1]][j - 1];
            }
            now++;
        } else if (t == '-') {
            int v;
            cin >> v;
            v--;
            unite(up[v][0], v);
        } else {
            int a, b;
            cin >> a >> b;
            a--; b--;
            cout << root(lca(a, b)) + 1 << endl;
        }
    }
    return 0;
}
