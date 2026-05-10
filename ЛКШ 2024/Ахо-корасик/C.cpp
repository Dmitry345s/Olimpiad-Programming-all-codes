#include<bits/stdc++.h>

using namespace std;

const int A = 26, MAX = 1e5 + 5;

struct Node {
    int p, pr, sl, fl;
    int go[A];
    Node() {
        p = 0;
        pr = 0;
        sl = 0;
        fl = 0;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);
vector<vector<int>> g(MAX);
vector<vector<pair<int, int>>> g2(MAX);

void add(string& s) {
    int v = 0;
    for (auto c : s) {
        int ch = c - 'a';
        if (bor[v].go[ch] == -1) {
            bor.push_back(Node());
            bor.back().pr = v;
            bor.back().p = ch;
            bor[v].go[ch] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch];
    }
    bor[v].fl += 1;
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].go[i] != -1) {
            q.push(bor[0].go[i]);
        } else {
            bor[0].go[i] = 0;
        }
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
            if (bor[v].go[i] != -1) {
                q.push(bor[v].go[i]);
            } else {
                bor[v].go[i] = bor[bor[v].sl].go[i];
            }
        }
    }
}

vector<int> pl(MAX);

void dfs(int v = 0, int p = 0, int now = 0) {
    for (auto [to, c] : g2[v]) {
        if (to == p) continue;
        //cout << to << " " << c << " " << now << " " << bor[now].go[c] << endl;
        pl[bor[now].go[c]]++;
        dfs(to, v, bor[now].go[c]);
    }
}

vector<long long> dp(MAX);

void dfs2(int v = 0, int p = 0) {
    dp[v] = pl[v];
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
        dp[v] += dp[to];
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int num;
            char c;
            cin >> num >> c;
            num--;
            int ch = c - 'a';
            g2[i].push_back({num, ch});
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    bfs();
    dfs();
    dfs2();
    long long ans = 0;
    for (int i = 0; i < (int)bor.size(); ++i) {
        if (!bor[i].fl) continue;
        ans += 1ll * dp[i] * bor[i].fl;
    }
    cout << ans << endl;
    return 0;
}
