#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e3, C = 0, C2 = 5;

int a[MAX];
int cnt[MAX];
vector<int> g[MAX];
int cnt2[MAX][MAX];
int d[MAX];
int p[MAX];

void calc(int v, int dv) {
    d[v] = dv;
    cnt2[dv][a[v]]++;
    for (int to : g[v]) {
        calc(to, dv + 1);
    }
}

/*int p[MAX], d[MAX];

vector<int> dp[MAX];
int cntd[MAX][C2];
int ana[MAX];
int andp[MAX];



int nowcnt[MAX][C2];
vector<pair<int, int>> segs[MAX];

void solve(int v) {
    for (int to : g[v]) {
        solve(to);
        for (int j = 0; j < C2; ++j) {
            nowcnt[v][j] += nowcnt[to][j];
        }
    }
    if (cnt[a[v]] > C) {
        nowcnt[v][ana[a[v]]]++;
    }
    segs[d[v]].push_back({andp[v], andp[v]});
    if ((int)g[v].size() == 0) {
        gd[(int)segs[d[v]].size() - 1] = -1;
    } else if ((int)g[v].size() == 1) {
        gd[(int)se]
    } else if ((int)g[v].size() > 1) {

    }
}*/

pair<int, int> ans;
int s;
int u[MAX];
int u2[MAX];

void upd(pair<int, int> tr) {
    if (tr.first > ans.first) {
        ans = tr;
        return;
    }
    if (tr.first < ans.first) return;
    if (tr.second < ans.second) {
        ans = tr;
        return;
    }
}

void dfses(int v, int dv) {
    if (a[v] == a[s]) {
        u[dv]++;
    }
    u2[dv]++;
    for (int to : g[v]) {
        dfses(to, dv + 1);
    }
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = 1; i < n; ++i) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }
    calc(0, 0);
    for (int i = 0; i < n; ++i) {
        fill(u, u + n, 0);
        fill(u2, u2 + n, 0);
        s = i;
        dfses(i, d[i]);
        pair<int, int> now = {1, 0};
        for (int j = 0; j < n; ++j) {
            if (j > d[i]) {
                int t = min(u2[j], cnt2[j][a[i]]);
                now.first += t;
                now.second += t - u[j];
            }
        }
        upd(now);
    }
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
