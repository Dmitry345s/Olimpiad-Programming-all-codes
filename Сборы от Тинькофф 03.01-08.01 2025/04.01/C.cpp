#include<bits/stdc++.h>

using namespace std;

const int MAX = 105;
int p[MAX];

int root(int v) {
    if (p[v] == v) return v;
    return p[v] = root(p[v]);
}

signed main() {
    int n;
    cin >> n;
    vector<array<vector<int>, 2>> all(7);
    vector<vector<int>> ch(n, vector<int> (7));
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < n; ++j) {
            all[i][!(j % (1 << (i + 1)) < (1 << i))].push_back(j);
            ch[j][i] = !(j % (1 << (i + 1)) < (1 << i));
        }
    }
    vector<vector<int>> cnt(n, vector<int> (n));
    vector<vector<int>> ha(n);
    for (int i = 0; i < n; ++i) {
        ha[i] = {i};
        p[i] = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        vector<int> ans(7);
        for (int j = 0; j < 7; ++j) {
            if (all[j][0].empty() || all[j][1].empty()) continue;
            int sz = 0;
            for (auto v : all[j][0]) {
                sz += (int)ha[v].size();
            }
            if (sz == n || sz == 0) continue;
            cout << "? ";
            cout << sz << " ";
            for (auto v : all[j][0]) {
                for (auto x : ha[v]) {
                    cout << x + 1 << " ";
                }
            }
            sz = 0;
            for (auto v : all[j][1]) {
                sz += (int)ha[v].size();
            }
            cout << sz << " ";
            for (auto v : all[j][1]) {
                for (auto x : ha[v]) {
                    cout << x + 1 << " ";
                }
            }
            cout << endl;
            string tr;
            cin >> tr;
            if (tr == "YES") {
                ans[j] = 1;
            }
        }
        array<vector<int>, 2> all;
        for (int v = 0; v < n; ++v) {
            for (int u = v + 1; u < n; ++u) {
                int flag = 1;
                if ((int)ha[u].size() == 0 || (int)ha[v].size() == 0) continue;
                for (int k = 0; k < 7; ++k) {
                    if (ch[v][k] != ch[u][k]) {
                        if (ans[k] == 0) {
                            flag = 0;
                        }
                    } else {
                        if (ans[k] == 1) {
                            flag = 0;
                        }
                    }
                }
                if (!flag) continue;
                int rv = v, ru = u;
                if ((int)ha[rv].size() > (int)ha[ru].size()) {
                    swap(ru, rv);
                }
                for (int x : ha[rv]) {
                    all[0].push_back(x);
                }
                for (int x : ha[ru]) {
                    all[1].push_back(x);
                }
            }
        }
        int l = 0, r = (int)all[0].size();
        while (l + 1 < r) {
            int m = (l + r) / 2;
            cout << "? " << (m - l) << " ";
            for (int k = l; k < m; ++k) {
                cout << all[0][k] + 1 << " ";
            }
            cout << (int)all[1].size() << " ";
            for (auto x : all[1]) {
                cout << x + 1 << " ";
            }
            cout << endl;
            string tr;
            cin >> tr;
            if (tr == "YES") {
                r = m;
            } else {
                l = m;
            }
        }
        int v = all[0][l];
        l = 0; r = (int)all[1].size();
        while (l + 1 < r) {
            int m = (l + r) / 2;
            cout << "? " << (m - l) << " ";
            for (int k = l; k < m; ++k) {
                cout << all[1][k] + 1 << " ";
            }
            cout << "1 " << v + 1 << endl;
            string tr;
            cin >> tr;
            if (tr == "YES") {
                r = m;
            } else {
                l = m;
            }
        }
        int u = all[1][l];
        cout << "! " << u + 1 << " " << v + 1 << endl;
        int ru = root(u), rv = root(v);
        p[ru] = rv;
        for (int x : ha[ru]) {
            ha[rv].push_back(x);
        }
        ha[ru].clear();
    }
    return 0;
}
