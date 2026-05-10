#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e3 + 1;
int a[MAX];
vector<int> g[MAX];

int dfs(int v, int p = -1) {
    int ans = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (a[to] < a[v]) {
            ans |= dfs(to, v);
        }
    }
    return !ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        if (dfs(i) == 0) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    return 0;
}
