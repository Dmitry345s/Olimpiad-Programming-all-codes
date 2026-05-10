#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    int p, pr;
    int sl;
    int to[A];
    int go[A];
    vector<int> fl;
    Node() {
        p = 0;
        pr = 0;
        fl = {};
        for (int i = 0; i < A; ++i) {
            to[i] = -1;
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(string s, int u) {
    int v = 0;
    for (auto c : s) {
        int ch = (int)c - 97;
        if (bor[v].to[ch] == -1) {
            bor.push_back(Node());
            bor.back().p = ch;
            bor.back().pr = v;
            bor[v].to[ch] = (int)bor.size() - 1;
        }
        v = bor[v].to[ch];
    }
    bor[v].fl.push_back(u);
}

int MAX = 2e6;
vector<vector<int>> g(MAX);
vector<int> pl(MAX), dp(MAX);

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].to[i] != -1) {
            q.push(bor[0].to[i]);
            bor[0].go[i] = bor[0].to[i];
            continue;
        }
        bor[0].go[i] = 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (bor[v].pr == 0) {
            bor[v].sl = 0;
        } else {
            bor[v].sl = bor[bor[bor[v].pr].sl].go[bor[v].p];
        }
        g[v].push_back(bor[v].sl);
        g[bor[v].sl].push_back(v);
        for (int i = 0; i < A; ++i) {
            if (bor[v].to[i] != -1) {
                bor[v].go[i] = bor[v].to[i];
                q.push(bor[v].to[i]);
                continue;
            }
            bor[v].go[i] = bor[bor[v].sl].go[i];
        }
    }
}

void dfs(int v = 0, int p = 0) {
    dp[v] = pl[v];
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        dp[v] += dp[to];
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string now;
        cin >> now;
        add(now, i);
    }
    bfs();
    string s;
    cin >> s;
    int now = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        int ch = (int)c - 97;
        now = bor[now].go[ch];
        //cout << now << endl;
        pl[now]++;
    }
    dfs();
    vector<int> ans(n);
    for (int i = 0; i < (int)bor.size(); ++i) {
        for (auto j : bor[i].fl) {
            ans[j] = dp[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
