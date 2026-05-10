#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    string s;
    cin >> s;
    int ans = 1e18;
    string ans2 = s;
    int n2 = s.size();
    for (int i = 0; i < n2; ++i) {
        char last = s[i];
        auto it = s.begin();
        for (int j = 0; j < i; ++j) {
            ++it;
        }
        s.erase(it);
        //cout << s << endl;
        for (int j = 0; j < n2; ++j) {
            auto it = s.begin();
            for (int l = 0; l < j; ++l) {
                ++it;
            }
            s.insert(it, last);
            //cout << s << endl;
            int x = 0, y = 0;
            int sum = 0;
            for (int l = 0; l < n2; ++l) {
                if (0 <= x && x < n && 0 <= y && y < m) {
                    sum += f[x][y];
                }
                if (s[l] == 'D') {
                    x += 1;
                }
                if (s[l] == 'R') {
                    y += 1;
                }
                if (s[l] == 'L') {
                    y -= 1;
                }
                if (s[l] == 'U') {
                    x -= 1;
                }
            }
            if (0 <= x && x < n && 0 <= y && y < m) {
                sum += f[x][y];
            }
            if (sum < ans) {
                ans = sum;
                ans2 = s;
            }
            it = s.begin();
            for (int l = 0; l < j; ++l) {
                it++;
            }
            s.erase(it);
        }
        it = s.begin();
        for (int j = 0; j < i; ++j) {
            it++;
        }
        s.insert(it, last);
    }
    cout << ans2 << endl;
    return 0;
}
