#include<bits/stdc++.h>

using namespace std;

struct Node {
    int sl, fl, p, p2, spl;
    int go[2];
    Node() {
        sl = 0;
        go[0] = -1;
        go[1] = -1;
        fl = 0;
        p = -1;
        p2 = -1;
        spl = 0;
    }
};

vector<Node> trie(1);

void add(string s) {
    int v = 0;
    for (auto c : s) {
        int cc = c - '0';
        if (trie[v].go[cc] == -1) {
            trie[v].go[cc] = (int)trie.size();
            trie.push_back(Node());
            trie.back().p = v;
            trie.back().p2 = cc;
        }
        v = trie[v].go[cc];
    }
    trie[v].fl = 1;
}

void build() {
    queue<int> q;
    if (trie[0].go[0] == -1) {
        trie[0].go[0] = 0;
    } else {
        q.push(trie[0].go[0]);
    }
    if (trie[0].go[1] == -1) {
        trie[0].go[1] = 0;
    } else {
        q.push(trie[0].go[1]);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        trie[v].sl = trie[trie[trie[v].p].sl].go[trie[v].p2];
        if (v == trie[v].sl) {
            trie[v].sl = 0;
        }
        trie[v].spl = trie[trie[v].sl].spl;
        if (trie[trie[v].sl].fl) {
            trie[v].spl = trie[v].sl;
        }
        for (int i = 0; i < 2; ++i) {
            if (trie[v].go[i] != -1) {
                q.push(trie[v].go[i]);
            } else {
                trie[v].go[i] = trie[trie[v].sl].go[i];
            }
        }
    }
}

const int MAX = 2e6;

vector<int> g[MAX];
int used[MAX], deg[MAX];

void dfs(int v, int t) {
    used[v] = t;
    if (t == 1) {
        for (int to : g[v]) {
            if (!used[to] && !(--deg[to]) && !(trie[to].spl != 0 || trie[to].fl)) {
                dfs(to, -1);
            }
        }
    } else {
        for (int to : g[v]) {
            if (!used[to]) {
                dfs(to, 1);
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string now;
        cin >> now;
        add(now);
    }
    build();
    string s;
    if (m != 0) {
        cin >> s;
    }
    int v = 0;
    for (int i = 0; i < m; ++i) {
        v = trie[v].go[s[i] - '0'];
    }
    for (int i = 0; i < (int)trie.size(); ++i) {
        deg[i] = 2;
        g[trie[i].go[0]].push_back(i);
        g[trie[i].go[1]].push_back(i);
    }
    for (int i = 0; i < (int)trie.size(); ++i) {
        if ((trie[i].spl != 0 || trie[i].fl) && !used[i]) {
            dfs(i, 1);
        }
    }
    if (used[v] == 0) {
        cout << "Friendship" << endl;
    } else if (used[v] == -1) {
        cout << "Iskander" << endl;
    } else {
        cout << "Olya" << endl;
    }
    return 0;
}
