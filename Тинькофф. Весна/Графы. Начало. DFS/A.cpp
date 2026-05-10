#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int> (n, 0));
    int i, j;
    for (int l = 0; l < m; ++l) {
        cin >> i >> j;
        g[i - 1][j - 1] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}
