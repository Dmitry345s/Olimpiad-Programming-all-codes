#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    int p, pr, sl, spl;
    int fl;
    int go[A];
    Node() {
        p = 0;
        pr = 0;
        sl = 0;
        spl = 0;
        fl = 0;
        for (int i = 0; i < A; ++i){
            go[i] = -1;
        }
    }
};

vector<Node> trie(1);

void add(string & s) {
    int v = 0;
    for (auto c : s) {
        int ch = c - 'a';
        if (trie[v].go[ch] == -1) {
            trie.push_back(Node());
            trie.back().pr = v;
            trie.back().p = ch;
            trie[v].go[ch] = (int)trie.size() - 1;
        }
        v = trie[v].go[ch];
    }
    trie[v].fl = 1;
}

const int MAX = 1e4, MOD = 1e4;
int used[MAX];

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (trie[0].go[i] != -1) {
            q.push(trie[0].go[i]);
            continue;
        }
        trie[0].go[i] = 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (trie[v].pr == 0) {
            trie[v].sl = 0;
        } else {
            trie[v].sl = trie[trie[trie[v].pr].sl].go[trie[v].p];
        }
        if (trie[trie[v].sl].fl) {
            trie[v].spl = trie[v].sl;
        } else {
            trie[v].spl = trie[trie[v].sl].spl;
        }
        if (trie[v].spl != 0 || trie[v].fl) {
            used[v] = 1;
        }
        for (int i = 0; i < A; ++i) {
            if (trie[v].go[i] != -1) {
                q.push(trie[v].go[i]);
            } else {
                trie[v].go[i] = trie[trie[v].sl].go[i];
            }
        }
    }
}

signed main() {
    //freopen("strings.in", "r", stdin);
    //freopen("strings.out", "w", stdout);
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    bfs();
    vector<vector<int>> dp(n + 1, vector<int> ((int)trie.size() + 1));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)trie.size(); ++j) {
            for (int k = 0; k < A; ++k) {
                if (used[trie[j].go[k]]) continue;
                dp[i + 1][trie[j].go[k]] += dp[i][j];
                dp[i + 1][trie[j].go[k]] %= MOD;
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        ans *= A;
        ans %= MOD;
    }
    int ans2 = 0;
    for (int i = 0; i < (int)trie.size(); ++i) {
        ans2 += dp[n][i];
        ans2 %= MOD;
    }
    cout << (ans - ans2 + MOD) % MOD  << endl;
    return 0;
}
