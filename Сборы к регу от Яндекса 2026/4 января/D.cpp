#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> st(int x) {
    vector<vector<int>> ans(x, vector<int> (x));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < x; ++j) {
            ans[i][j] = (j - i + x) % x;
        }
    }
    return ans;
}

const int MAX = 1000;
int pr[MAX];
int us[MAX];
int cnt = 0;

bool try_kuhn(int v, vector<vector<int>> & g) {
    if (us[v] == cnt) return false;
    us[v] = cnt;
    for (int to : g[v]) {
        if (pr[to] == -1) {
            pr[to] = v;
            return true;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(pr[to], g)) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> to_pars(vector<vector<int>> g, int n) {
    for (int i = 0; i < n; ++i) {
        pr[i] = -1;
        us[i] = 0;
    }
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        int y = try_kuhn(i, g);
        if (!y) {
            cnt++;
            y = try_kuhn(i, g);
        }
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back({pr[i], i});
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> now = st(a[0]);
    for (int x = 1; x < n; ++x) {
        if (a[x - 1] * 2 > a[x]) {
            cout << "No" << endl;
            return 0;
        }
    }
    for (int x = 1; x < n; ++x) {
        vector<vector<int>> rans(a[x], vector<int> (a[x], a[x]));
        int y = a[x] - a[x - 1];
        for (int i = 0; i < a[x - 1]; ++i) {
            for (int j = 0; j < a[x - 1]; ++j) {
                rans[i][j] = now[i][j];
            }
        }
        vector<vector<int>> u = st(y);
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < y; ++j) {
                rans[i + a[x - 1]][j + a[x - 1]] = u[i][j];
            }
        }
        for (int i = 0; i < a[x]; ++i) {
            for (int j = 0; j < a[x]; ++j) {
                if (rans[i][j] >= a[x - 1]) {
                    rans[i][j] = -1;
                }
            }
        }
        vector<vector<int>> g(a[x]);
        for (int i = 0; i < a[x]; ++i) {
            for (int j = 0; j < a[x]; ++j) {
                if (rans[i][j] == -1) {
                    g[i].push_back(j);
                }
            }
        }
        for (int u = a[x - 1]; u < a[x]; ++u) {
            vector<pair<int, int>> tt = to_pars(g, a[x]);
            for (auto [i, j] : tt) {
                rans[i][j] = u;
                g[i].erase(lower_bound(g[i].begin(), g[i].end(), j));
            }
        }
        swap(now, rans);
    }
    cout << "Yes" << endl;
    for (int i = 0; i < (int)now.size(); ++i) {
        for (int j = 0; j < (int)now.size(); ++j) {
            cout << now[i][j] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
