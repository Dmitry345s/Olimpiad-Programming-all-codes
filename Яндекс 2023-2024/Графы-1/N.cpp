#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<int>> g(MAX);

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    return 0;
}
