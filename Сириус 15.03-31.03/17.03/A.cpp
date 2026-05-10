#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
int flag = 0;

void dfs(int v) {
    used[v] = -1;
    for (int to : g[v]) {
        if (used[to] == -1) {
            flag = 1;
        }
        if (used[to] == 0) {
            dfs(to);
        }
    }
    used[v] = 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> used2(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int a;
            cin >> a;
            --a;
            g[i].push_back(a);
        }
        if (c == 0) {
            used2[i] = 1;
        }
    }
    int s;
    cin >> s;
    --s;
    dfs(s);
    vector<int> used3(n);
    vector<array<int, 2>> d(n, {0, 0});
    vector<array<int, 2>> p(n, {-1, -1});
    d[s][0] = 1;
    queue<int> q;
    q.push(s);
    used3[s] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (used3[to] >= 3) continue;
            array<int, 2> dnew;
            dnew[0] = (d[v][1] | d[to][0]);
            dnew[1] = (d[v][0] | d[to][1]);
            if (dnew != d[to]) {
                if (d[v][1] && d[to][0] != 1) {
                    p[to][0] = v;
                }
                if (d[v][0] && d[to][1] != 1) {
                    p[to][1] = v;
                }
                d[to] = dnew;
                q.push(to);
                used3[to]++;
            }
        }
    }
    int v = -1;
    for (int i = 0; i < n; ++i) {
        if (used2[i] && d[i][1] == 1) {
            v = i;
        }
    }
    if (v == -1) {
        if (flag) {
            cout << "Draw" << endl;
        } else {
            cout << "Lose" << endl;
        }
        return 0;
    }
    vector<int> rans;
    int cnt = 1;
    while (v != -1 && rans.size() <= 1e7) {
        rans.push_back(v);
        v = p[v][cnt];
        cnt ^= 1;
    }
    if (v == s) {
        rans.push_back(s);
    }
    reverse(rans.begin(), rans.end());
    if (rans.size() >= 10 * n) {
        if (flag) {
            cout << "Draw" << endl;
        } else {
            cout << "Lose" << endl;
        }
        return 0;
    }
    cout << "Win" << endl;
    for (int i = 0; i < rans.size(); ++i) {
        cout << rans[i] + 1 << " ";
    }
    return 0;
}
