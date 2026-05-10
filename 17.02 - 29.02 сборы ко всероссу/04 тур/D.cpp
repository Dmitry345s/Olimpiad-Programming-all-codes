#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> f;
vector<vector<int>> used;

void dfs(int x, int y, vector<vector<int>> & a, vector<vector<int>> & b, int num) {
    f[x][y] = num;
    if (x + 1 < n && b[x][y] && f[x + 1][y] == -1) {
        dfs(x + 1, y, a, b, num);
    }
    if (y + 1 < m && a[x][y] && f[x][y + 1] == -1) {
        dfs(x, y + 1, a, b, num);
    }
    if (x - 1 >= 0 && b[x - 1][y] && f[x - 1][y] == -1) {
        dfs(x - 1, y, a, b, num);
    }
    if (y - 1 >= 0 && a[x][y - 1] && f[x][y - 1] == -1) {
        dfs(x, y - 1, a, b, num);
    }
}

signed main() {
    int q;
    cin >> n >> m >> q;
    f.assign(n, vector<int> (m, -1));
    vector<vector<int>> a(n, vector<int> (m - 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    vector<vector<int>> b(n - 1, vector<int> (m));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            b[i][j] = c - '0';
        }
    }
    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    int num = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == -1) {
                dfs(i, j, a, b, num);
                num++;
            }
        }
    }
    vector<int> l(num);
    vector<int> r(num);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            l[f[i][j]] = min(l[f[i][j]], i);
            r[f[i][j]] = max(r[f[i][j]], i);
        }
    }
    int qs;
    cin >> qs;
    vector<pair<int, int>> ls;
    for (int i = 0; i < num; ++i) {
        ls.push_back({l[i], i});
    }
    sort(ls.begin(), ls.end());
    for (int i = 0; i < qs; ++i) {
        int k;
        cin >> k;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1; --y1; --x2; --y2;
        int in1 = f[x1][y1], in2 = f[x2][y2];
        if (r[in1] >= r[in2]) {
            swap(in1, in2);
        }
        int u = 0;
        int cnt = 0;
        while (u < num && r[in1] < l[in2]) {
            cnt++;
            int maxm = 0;
            int in3 = -1;
            while (u < num && ls[u].first <= r[in1]) {
                if (r[ls[u].second] >= maxm) {
                    in3 = ls[u].second;
                    maxm = r[ls[u].second];
                }
                ++u;
            }
            in1 = in3;
        }
        if (r[in1] < l[in2]) {
            cout << -1 << endl;
        } else {
            cout << cnt << endl;
        }
    }
    return 0;
}
