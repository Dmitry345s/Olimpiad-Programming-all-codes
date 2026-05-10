#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(30000);
vector<int> sz(30000);

void dfs(int v, int p = 0) {
    sz[v] = sz[p] + 1;
    for (int to : g[v]) {
        if (to != p) {
            dfs(to, v);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    --a; --b;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        cin >> p[i];
        --p[i];
        g[p[i]].push_back(i);
    }
    sz[0] = -1;
    dfs(0);
    if (sz[a] > sz[b]) {
        swap(a, b);
    }
    int k = sz[b];
    for (int i = 0; i < k - sz[a]; ++i) {
        b = p[b];
    }
    while (a != b) {
        a = p[a];
        b = p[b];
    }
    cout << a + 1 << endl;
    return 0;

}
