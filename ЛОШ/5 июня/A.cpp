#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int a, x, b, y, z;
    cin >> a >> x >> b >> y >> z;
    if (a > b) {
        swap(a, b);
        swap(x, y);
    }
    int sum = a + b;
    int cnt = 0;
    vector<pair<int, int>> ans;
    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            if (i * x + j * y == z) {
                ans.push_back({i, j});
            }
        }
    }
    vector<vector<int>> ab(a + 1, vector<int> (b + 1, -1));
    ab[0][0] = 0;
    for (int i = 0; i < a + 1; ++i) {
        for (int j = 0; j < b + 1; ++j) {
            for (int l = 0; l < int(ans.size()); ++l) {
                if (i - ans[l].first >= 0 && j - ans[l].second >= 0) {
                    int p = i - ans[l].first, p2 = j - ans[l].second;
                    if (ab[p][p2] != -1) {
                        ab[i][j] = max(ab[i][j], ab[p][p2] + 1);
                    }
                }
            }
            cnt = max(cnt, ab[i][j]);
        }
    }
    cout << sum - cnt << endl;
    return 0;
}
