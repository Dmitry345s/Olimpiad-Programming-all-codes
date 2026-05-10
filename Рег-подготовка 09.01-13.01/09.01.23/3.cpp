#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(10000);
vector<bool> used(10000);
pair<vector<int>, vector<int>> components;

void dfs(int v, int t = 0){
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i){
        int to = g[v][i];
        if (!used[to]){
            if (1 - t == 0){
                components.first.push_back(to);
            } else{
                components.second.push_back(to);
            }
            dfs(to, 1 - t);
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    int i, j;
    for (int l = 0; l < m; ++l){
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    if (m == 0){
        cout << n / 2 * (n - n / 2) << endl;
        return 0;
    }
    vector<pair<int, int>> sizes;
    sizes.push_back({-1, -1});
    for (int i = 0; i < n; ++i){
        if (!used[i]){
            components.first.push_back(i);
            dfs(i);
            sizes.push_back({components.first.size(), components.second.size()});
            components.first.clear();
            components.second.clear();
        }
    }
    vector<vector<bool>> backbag(sizes.size(), vector<bool> (n / 2 + 1, false));
    backbag[0][0] = true;
    for (int i = 1; i < sizes.size(); ++i){
        for (int j = 0; j <= n / 2; ++j){
            if (j - sizes[i].first >= 0 && !backbag[i][j]){
                backbag[i][j] = backbag[i - 1][j - sizes[i].first];
            }
            if (j - sizes[i].second >= 0 && !backbag[i][j]){
                backbag[i][j] = backbag[i - 1][j - sizes[i].second];
            }
        }
    }
    int maxm = -1e9;
    for (int i = 0; i < backbag.back().size(); ++i){
        if (backbag.back()[i]){
            maxm = max(maxm, i);
        }
    }
    cout << maxm * (n - maxm) - m << endl;
    return 0;
}
