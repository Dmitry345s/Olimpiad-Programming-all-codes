#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int max_size = 200000;

vector<vector<int>> g(max_size), g2(max_size);
vector<int> topsort, used(max_size, -1);

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
    cout << num + 1 << endl;
    for (int i = 0; i < n; ++i) {
        cout << used[i] + 1 << " ";
    }
    return 0;
}
