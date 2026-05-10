#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int num = 0;
int MAX = 1e5;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
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

void dfs2 (int v) {
    used[v] = num;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs2(to);
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(top_sort.begin(), top_sort.end());
    for (int i = 0; i < int(top_sort.size()); ++i) {
        int v = top_sort[i];
        if (!used[v]) {
            ++num;
            dfs2(v);
        }
    }
    return 0;
}
