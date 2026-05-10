//#define _GLIBCXX_DEBUG
#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(1488);
const int MAX = 101;
vector<vector<int>> g(MAX);
vector<int> used(MAX), used2(MAX);
vector<vector<int>> to_check(MAX, vector<int> (MAX));
bool flag = 0;

void dfs(int v, int st) {
    to_check[st][v] = 1;
    used2[v] = -1;
    for (int to : g[v]) {
        if (used2[to] == 1) continue;
        if (used2[to] == -1) {
            flag = 1;
            return;
        }
        dfs(to, st);
    }
    used2[v] = 1;
}

vector<vector<int>> g3(MAX);
vector<int> now_pair(MAX, -1);
int timer = 1;

bool try_kuhn(int v) {
    if (used[v]) return 0;
    used[v] = 1;
    for (int to : g3[v]) {
        if (now_pair[to] == -1) {
            now_pair[to] = v;
            return 1;
        }
    }
    for (int to : g3[v]) {
        if (try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}

vector<vector<int>> g2(2 * MAX);
vector<int> used3(2 * MAX);

void dfs2(int v) {
    used3[v] = 1;
    for (int to : g2[v]) {
        if (used3[to]) continue;
        dfs2(to);
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int st;
            cin >> st;
            if (st) {
                g[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        used2.assign(n, 0);
        dfs(i, i);
    }
    //cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (to_check[i][j] == 0 || i == j) continue;
            g3[i].push_back(j);
        }
    }
    for (int i = 0; i < n; ++i) {
        used.assign(n, 0);
        if (try_kuhn(i)) {
            timer++;
        }
    }
    //cout << 1 << endl;
    vector<int> now_pair2(n, -1);
    for (int i = 0; i < n; ++i) {
        if (now_pair[i] != -1) {
            now_pair2[now_pair[i]] = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (to_check[i][j] == 0 || i == j) continue;
            if (now_pair2[i] != j) {
                g2[i].push_back(j + n);
            } else {
                g2[j + n].push_back(i);
            }
        }
    }
    timer = 1;
    for (int i = 0; i < n; ++i) {
        if (now_pair2[i] == -1) {
            timer++;
            dfs2(i);
        }
    }
    vector<int> check(n, 1);
    for (int i = 0; i < n; ++i) {
        if (!used3[i]) {
            check[i] = 0;
        }
    }
    for (int i = n; i < n + n; ++i) {
        if (used3[i]) {
            check[i - n] = 0;
        }
    }
    //swap(pth[0], pth[1]);
    cout << timer - 1 << endl;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (check[i]) {
            cnt++;
            cout << i + 1 << " ";
        }
    }
    assert(timer - 1 <= cnt);
    cout << endl;
    return 0;
}
