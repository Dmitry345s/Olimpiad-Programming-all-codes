#include<bits/stdc++.h>

using namespace std;

const int MAX = 500;

mt19937 rnd(179);

vector<int> g[MAX];
int used[MAX];
vector<int> now;

void dfs(int v) {
    used[v] = 1;
    now.push_back(v);
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> st(n);
    for (int i = 0; i < n; ++i) {
        st[i] = i;
    }
    int stcnt;
    for (int i = 0; i < n; ++i) {
        cout << st[i] + 1 << " ";
    }
    cout << endl;
    cin >> stcnt;
    if (stcnt == -1 || stcnt == n) return 0;
    vector<vector<int>> mb(n, vector<int> (n, 1));
    vector<int> rans(n, -1);
    vector<pair<int, int>> mn, pl;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (rans[i] != -1 || rans[j] != -1) continue;
            swap(st[i], st[j]);
            for (int u = 0; u < n; ++u) {
                cout << st[u] + 1 << " ";
            }
            cout << endl;
            int cnt;
            cin >> cnt;
            if (cnt == -1 || cnt == n) return 0;
            swap(st[i], st[j]);
            int dif = cnt - stcnt;
            if (dif == 0) {
                mb[i][i] = 0;
                mb[i][j] = 0;
                mb[j][i] = 0;
                mb[j][j] = 0;
                continue;
            }
            if (dif == -2) {
                st[i] = i;
                st[j] = j;
                rans[i] = 0;
                rans[j] = 0;
            } else if (dif == 2) {
                st[i] = j;
                st[j] = i;
                rans[i] = 0;
                rans[j] = 0;
                stcnt += 2;
            } else if (dif == 1) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (rans[i] == -1) {
            fill(used, used + n, 0);
            now.clear();
            dfs(i);
            vector<int> q = st;
            for (int j = 0; j < (int)now.size(); ++j) {
                int j2 = (j + 1) % (int)now.size();
                q[now[j2]] = now[j];
            }
            for (int j = 0; j < n; ++j) {
                cout << q[j] + 1 << " ";
            }
            cout << endl;
            int cnt;
            cin >> cnt;
            if (cnt == -1 || cnt == n) return 0;
            if (cnt == stcnt) {
                for (int j = 0; j < (int)now.size(); ++j) {
                    int j2 = (j - 1 + (int)now.size()) % (int)now.size();
                    st[now[j2]] = now[j];
                    rans[now[j2]] = 0;
                }
            } else {
                for (int j = 0; j < (int)now.size(); ++j) {
                    int j2 = (j + 1) % (int)now.size();
                    st[now[j2]] = now[j];
                    rans[now[j2]] = 0;
                }
            }
            stcnt += (int)now.size();
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << st[i] + 1 << " ";
    }
    cout << endl;
    int cnt;
    cin >> cnt;
    return 0;
}
