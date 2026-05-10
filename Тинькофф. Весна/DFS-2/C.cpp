#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

vector<vector<int>> g(10000), g2(10000);
vector<int> topsort, used(10000, -1), used2(10000, 0);
set<pair<int, int>> f;

void dfs1(int v) {
    used[v] = 0;
    for (int to : g[v]) {
        if (used[to] == -1) {
            dfs1(to);
        }
    }
    topsort.push_back(v);
}

void dfs2(int v, int num) {
    used[v] = num;
    for (int to : g2[v]) {
        if (used[to] == -1) {
            dfs2(to, num);
        }
    }
}
void dfs3(int v) {
    used2[v] = 1;
    for (int to : g[v]) {
        if (used[v] != used[to]) {
            f.insert({used[v], used[to]});
        }
        if (used2[to] == 0) {
            dfs3(to);
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int l = 0; l < m; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g2[j - 1].push_back(i - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1) {
            dfs1(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n; ++i) {
        used[i] = -1;
    }
    int num = -1;
    for (int i = 0; i < n; ++i) {
        int v = topsort[i];
        if (used[v] == -1) {
            num += 1;
            dfs2(v, num);
        }
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        if (used2[i] == 0) {
            dfs3(i);
        }
    }
    cout << f.size() << endl;
    return 0;
}
