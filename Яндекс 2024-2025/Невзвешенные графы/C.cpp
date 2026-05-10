#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e2;
vector<int> gl[MAX];
vector<int> gr[MAX];
int used[MAX];
int used2[MAX];
int pr[MAX];
int pr2[MAX];

bool try_kuhn(int v) {
    if (used[v]) return 0;
    used[v] = 1;
    for (int to : gl[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to])) {
            pr[to] = v;
            pr2[v] = to;
            return 1;
        }
    }
    return 0;
}

void dfs(int v, int t) {
    if (t == 0) {
        if (used[v]) return;
        used[v] = 1;
        for (int to : gl[v]) {
            if (to == pr2[v]) continue;
            dfs(to, 1);
        }
    } else {
        if (used2[v]) return;
        used2[v] = 1;
        dfs(pr[v], 0);
    }
}

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> m >> n;
        for (int i = 0; i < n; ++i) {
            gl[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            gr[i].clear();
            vector<int> ch(n);
            while (true) {
                int a;
                cin >> a;
                --a;
                if (a == -1) break;
                ch[a] = 1;
            }
            for (int j = 0; j < n; ++j) {
                if (!ch[j]) {
                    gr[i].push_back(j);
                    gl[j].push_back(i);
                }
            }
        }
        fill(pr, pr + m, -1);
        fill(pr2, pr2 + n, -1);
        for (int i = 0; i < n; ++i) {
            fill(used, used + n, 0);
            try_kuhn(i);
        }
        fill(used, used + n, 0);
        fill(used2, used2 + m, 0);
        for (int i = 0; i < n; ++i) {
            if (pr2[i] == -1) {
                dfs(i, 0);
            }
        }
        vector<int> ans1;
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                ans1.push_back(i);
            }
        }
        vector<int> ans2;
        for (int i = 0; i < m; ++i) {
            if (!used2[i]) {
                ans2.push_back(i);
            }
        }
        cout << (int)ans1.size() + (int)ans2.size() << endl;
        cout << (int)ans2.size() << " " << (int)ans1.size() << endl;
        for (int v : ans2) {
            cout << v + 1 << " ";
        }
        cout << endl;
        for (int v : ans1) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
