#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> s(m, vector<int> (n));
    vector<vector<int>> us(m, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> s[i][j];
            s[i][j]--;
        }
    }
    vector<int> now;
    for (int i = 0; i < n; ++i) {
        now.push_back(i);
    }
    vector<int> ans;
    while ((int)now.size() > 1) {
        int in = -1;
        for (int i = 0; i < m; ++i) {
            vector<int> ch(n);
            for (int j = 0; j < n; ++j) {
                if (!us[i][j]) {
                    ch[s[i][j]] = 1;
                }
            }
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (ch[i]) {
                    cnt++;
                }
            }
            if (cnt < (int)now.size()) {
                in = i;
                break;
            }
        }
        vector<int> ch(n);
        for (int j = 0; j < n; ++j) {
            if (!us[in][j]) {
                ch[s[in][j]] = 1;
            }
        }
        for (int v : now) {
            if (!ch[v]) {
                for (int j = 0; j < m; ++j) {
                    us[j][v] = 0;
                }
            }
        }
        now.clear();
        for (int i = 0; i < n; ++i) {
            if (ch[i]) {
                now.push_back(i);
                for (int j = 0; j < m; ++j) {
                    us[j][i] = 1;
                }
            } else {
                for (int j = 0; j < m; ++j) {
                    us[j][i] = 0;
                }
            }
        }
        ans.push_back(in);
    }
    cout << now[0] << endl;
    for (int v : ans) {
        cout << v << endl;
    }
    return 0;
}
