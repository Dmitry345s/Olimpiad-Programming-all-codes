#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int MAX = 2e9 + 179;
    vector<vector<int>> d(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
            if (d[i][j] == 0 && i != j) {
                d[i][j] = MAX;
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < MAX && d[k][j] < MAX) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    vector<vector<int>> ans(n, vector<int> (n, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] == MAX) {
                ans[i][j] = 0;
                continue;
            }
            for (int t = 0; t < n; ++t) {
                if (d[i][t] != MAX && d[t][j] != MAX && d[t][t] < 0) {
                    ans[i][j] = 2;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
    }
    return 0;
}
