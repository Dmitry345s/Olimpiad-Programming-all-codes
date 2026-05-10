#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

vector<int> used(10000);
vector<int> component(10000);
set<pair<int, int>> c;
vector<vector<int>> g(10000);
vector<vector<int>> g2(10000);
vector<int> top_sort;

void dfs0(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs0(to);
        }
    }
    top_sort.push_back(v);
}

void dfs1(int v, int num) {
    used[v] = 1;
    component[v] = num;
    for (int to : g2[v]) {
        if (!used[to]) {
            dfs1(to, num);
        }
    }
}

void dfs2(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (component[v] != component[to]) {
            c.insert({component[v], component[to]});
        }
        if (!used[to]) {
            dfs2(to);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> field(n + 2, vector<int> (m + 2, 100001));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            cin >> field[i][j];
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (field[i - 1][j] <= field[i][j]) {
                g[(i - 1) * m + j - 1].push_back((i - 2) * m + j - 1);
                g2[(i - 2) * m + j - 1].push_back((i - 1) * m + j - 1);
            }
            if (field[i + 1][j] <= field[i][j]) {
                g[(i - 1) * m + j - 1].push_back(i * m + j - 1);
                g2[i * m + j - 1].push_back((i - 1) * m + j - 1);
            }
            if (field[i][j - 1] <= field[i][j]) {
                g[(i - 1) * m + j - 1].push_back((i - 1) * m + j - 2);
                g2[(i - 1) * m + j - 2].push_back((i - 1) * m + j - 1);
            }
            if (field[i][j + 1] <= field[i][j]) {
                g[(i - 1) * m + j - 1].push_back((i - 1) * m + j);
                g2[(i - 1) * m + j].push_back((i - 1) * m + j - 1);
            }
        }
    }
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            dfs0(i);
        }
    }
    reverse(top_sort.begin(), top_sort.end());
    for (int i = 0; i < n * m; ++i) {
        used[i] = 0;
    }
    int num = 0;
    for (int i = 0; i < top_sort.size(); ++i) {
        int v = top_sort[i];
        if (!used[v]) {
            num++;
            dfs1(v, num);
        }
    }
    for (int i = 0; i < n * m; ++i) {
        used[i] = 0;
    }
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            dfs2(i);
        }
    }
    vector<vector<int>> g3(num);
    for (auto x : c) {
        g3[x.first - 1].push_back(x.second - 1);
    }
    int ans = 0;
    for (int i = 0; i < g3.size(); ++i) {
        if (g3[i].size() == 0) {
            ans += 1;
        }
    }
    cout << ans << endl;
}
