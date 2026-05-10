#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int MAX = 1e9 + 179;
    vector<vector<int>> d(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
            if (d[i][j] == -1) {
                d[i][j] = MAX;
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(d[i][j] == MAX)) {
                ans = max(ans, d[i][j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
