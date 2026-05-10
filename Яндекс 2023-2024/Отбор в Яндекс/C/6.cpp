#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    vector<vector<int>> sh(2001, vector<int> (2001));
    for (int i = 0; i < 4; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 1000;
        y1 += 1000;
        x2 += 1000;
        y2 += 1000;
        for (int j = x1; j < x2; ++j) {
            for (int l = y1; l < y2; ++l) {
                sh[j][l] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 2001; ++i) {
        for (int j = 0; j < 2001; ++j) {
            ans += sh[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}
