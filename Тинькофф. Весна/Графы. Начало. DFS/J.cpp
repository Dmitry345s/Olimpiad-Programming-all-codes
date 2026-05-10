#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#define ll long long

using namespace std;

vector<vector<int>> components;
vector<bool> used(10000, false);
vector<vector<int>> g(10000);
bool flag = true;
vector<int> parents(100, -1);
int nums_of_components = 0;

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
}

int num(int i, int j, int& m, int& n) {
    return (i - 1) * n + j - 1;
}

int main() {
    int n, m;
    cin >> m >> n;
    vector<vector<char>> table(m + 2, vector<char> (n + 2));
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            cin >> table[i][j];
        }
    }
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            if (table[i][j] == '.') {
                used[num(i, j, m, n)] = true;
                continue;
            }
            if (table[i - 1][j] == '#') {
                g[num(i, j, m, n)].push_back(num(i - 1, j, m, n));
            }
            if (table[i][j - 1] == '#') {
                g[num(i, j, m, n)].push_back(num(i, j - 1, m, n));
            }
            if (table[i + 1][j] == '#') {
                g[num(i, j, m, n)].push_back(num(i + 1, j, m, n));
            }
            if (table[i][j + 1] == '#') {
                g[num(i, j, m, n)].push_back(num(i, j + 1, m, n));
            }
        }
    }
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            nums_of_components += 1;
            dfs(i);
        }
    }
    cout << nums_of_components << endl;
    return 0;
}
