#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> g(100000);
vector<int> used(100000);
vector<int> tin(100000), tout(100000);
int time_ = 0;

void dfs(int v) {
    used[v] = 1;
    tin[v] = time_++;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    tout[v] = time_++;
}

int main() {
    int n;
    cin >> n;
    int k, l;
    for (int i = 0; i < n; ++i) {
        cin >> k;
        if (k == 0) {
            l = i;
            continue;
        }
        g[k - 1].push_back(i);
    }
    dfs(l);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (tin[a] < tin[b] && tout[b] < tout[a]) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
}
