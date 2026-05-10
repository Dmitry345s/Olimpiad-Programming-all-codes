#include<bits/stdc++.h>
#include "grader.h"

using namespace std;

const int LN = 12;
const int MAX = 1500;
vector<int> g[MAX];
int us[MAX];
int cnt[3];
int fl = 1;

void dfs(int v, int num) {
    cnt[num]++;
    us[v] = num;
    for (int to : g[v]) {
        if (us[to] == num) fl = 0;
        if (us[to]) continue;
        dfs(to, ((num - 1) ^ 1) + 1);
    }
}

/*void InitMap(int a, int b) {
    cout << a << " " << b << endl;
}

void MakeMap(int a, int b) {
    cout << a << " " << b << endl;
}

void InitG(int a, int b) {
    cout << a << " " << b << endl;
}

void MakeG(int pos, int a, int b) {
    cout << a << " " << b << endl;
}*/

void Alice(int n, int m, int a[], int b[]) {
    int now = 0;
    vector<pair<int, int>> ans;
    for (int i = 0; i < m; ++i) {
        for (int j = now; j < now + a[i] + 1; ++j) {
            for (int j2 = now + a[i] + 1; j2 < now + a[i] + b[i] + 2; ++j2) {
                //cout << j << " " << j2 << endl;
                ans.push_back({j, j2});
            }
        }
        now += a[i] + 2 + b[i];
    }
    for (int i = now; i < now + n; ++i) {
        for (int j = i + 1; j < now + n; ++j) {
            ans.push_back({i, j});
        }
    }
    now += n;
    assert(now <= 1500);
    InitG(now, (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        MakeG(i, ans[i].first, ans[i].second);
    }
}

void Bob(int v, int u, int c[], int d[]) {
    if (v == 1) {
        InitMap(1, 0);
        return;
    }
    for (int i = 0; i < v; ++i) {
        g[i].clear();
        us[i] = 0;
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < u; ++i) {
        g[c[i]].push_back(d[i]);
        g[d[i]].push_back(c[i]);
    }
    int n = -1;
    for (int i = 0; i < v; ++i) {
        if (!us[i]) {
            cnt[1] = 0;
            cnt[2] = 0;
            fl = 1;
            dfs(i, 1);
            if (fl == 0 || cnt[1] + cnt[2] == 2) {
                n = cnt[1] + cnt[2];
            } else {
                ans.push_back({cnt[1] - 1, cnt[2] - 1});
            }
        }
    }
    InitMap(n, (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        MakeMap(ans[i].first, ans[i].second);
    }
}

/*signed main() {
    int t, n, m;
    cin >> t >> n >> m;
    int a[m], b[m];
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
    }
    if (t == 1) {
        Alice(n, m, a, b);
    } else {
        Bob(n, m, a, b);
    }
    return 0;
}*/
