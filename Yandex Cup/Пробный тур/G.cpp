#include<bits/stdc++.h>

//#define int long long

using namespace std;

const int MAX = 1e5 + 5, A = 26, C = 1e6 + 1;
int tin[MAX];
int sz[MAX];
vector<int> g[MAX];
vector<int> ord;
int timer = 0;
string all[MAX];

void dfs(int v) {
    sz[v] = 1;
    tin[v] = timer++;
    ord.push_back(v);
    for (int to : g[v]) {
        dfs(to);
        sz[v] += sz[to];
    }
}

struct Node {
    int sl, fl, smsl;
    int go[A];
    int p, p2;
    Node() {
        sl = 0;
        fl = 0;
        smsl = 0;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
        p = -1;
        p2 = -1;
    }
};

void add(vector<Node> & tr, string to_a) {
    int v = 0;
    for (char i : to_a) {
        int c = i - 'A';
        if (tr[v].go[c] == -1) {
            tr[v].go[c] = (int)tr.size();
            tr.push_back(Node());
            tr[tr[v].go[c]].p = v;
            tr[tr[v].go[c]].p2 = c;
        }
        v = tr[v].go[c];
    }
    tr[v].fl += 1;
}

void bfs(vector<Node> & tr) {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (tr[0].go[i] == -1) {
            tr[0].go[i] = 0;
        } else {
            q.push(tr[0].go[i]);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        tr[v].sl = tr[tr[tr[v].p].sl].go[tr[v].p2];
        if (v == tr[v].sl) {
            tr[v].sl = 0;
        }
        tr[v].smsl = tr[v].fl + tr[tr[v].sl].smsl;
        for (int i = 0; i < A; ++i) {
            if (tr[v].go[i] == -1) {
                tr[v].go[i] = tr[tr[v].sl].go[i];
            } else {
                q.push(tr[v].go[i]);
            }
        }
    }
}

vector<Node> rbuild(vector<string> now) {
    vector<Node> tr(1);
    for (auto v : now) {
        add(tr, v);
    }
    bfs(tr);
    return tr;
}

long long go(vector<Node> & tr, string s) {
    long long ans = 0;
    int v = 0;
    for (char c : s) {
        v = tr[v].go[c - 'A'];
        ans += tr[v].smsl;
    }
    return ans;
}

vector<pair<int, string>> to_ans[4 * MAX];

void gett(int v, int l, int r, int ql, int qr, string & t, int i) {
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        to_ans[v].push_back({i, t});
        return;
    }
    int m = (l + r) / 2;
    gett(2 * v, l, m, ql, qr, t, i);
    gett(2 * v + 1, m, r, ql, qr, t, i);
}

long long ans[MAX];

void build(int v, int l, int r) {
    vector<string> now;
    for (int i = l; i < r; ++i) {
        now.push_back(all[ord[i]]);
    }
    vector<Node> noww = rbuild(now);
    for (auto [in, t] : to_ans[v]) {
        ans[in] += go(noww, t);
    }
    noww.clear();
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> all[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }
    dfs(0);
    for (int i = 0; i < q; ++i) {
        int v;
        string t;
        cin >> v >> t;
        --v;
        gett(1, 0, n, tin[v], tin[v] + sz[v], t, i);
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
