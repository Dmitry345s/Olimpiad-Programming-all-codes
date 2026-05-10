#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    int go[A];
    int fl;
    int sl;
    int spl;
    int p, p2;
    Node() {
        for (int i = 0; i < A; ++i) go[i] = -1;
        fl = 0;
        sl = 0;
        spl = 0;
        p = -1;
        p2 = -1;
    }
};

vector<Node> bor(1);

void add(string s) {
    int v = 0;
    for (auto cc : s) {
        int c = cc - 'a';
        if (bor[v].go[c] == -1) {
            bor[v].go[c] = (int)bor.size();
            bor.push_back(Node());
            bor.back().p = v;
            bor.back().p2 = c;
        }
        v = bor[v].go[c];
    }
    bor[v].fl = 1;
}

vector<int> h;

void bfs() {
    h.assign((int)bor.size(), -1);
    h[0] = 0;
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].go[i] != -1) {
            h[bor[0].go[i]] = 1;
            q.push(bor[0].go[i]);
        } else {
            bor[0].go[i] = 0;
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        bor[v].sl = bor[bor[bor[v].p].sl].go[bor[v].p2];
        if (bor[v].sl == v) bor[v].sl = 0;
        bor[v].spl = bor[v].sl;
        if (!bor[bor[v].spl].fl) {
            bor[v].spl = bor[bor[v].spl].spl;
        }
        for (int i = 0; i < A; ++i) {
            if (bor[v].go[i] != -1) {
                h[bor[v].go[i]] = h[v] + 1;
                q.push(bor[v].go[i]);
            } else {
                bor[v].go[i] = bor[bor[v].sl].go[i];
            }
        }
    }
}

const int MAX = 1e6 + 1;
vector<int> g[MAX];
int rh[MAX];
int us[MAX];
int tin[MAX];
int tout[MAX];
int timer = 0;

void dfs(int v, int nh) {
    rh[v] = nh;
    us[v] = 1;
    tin[v] = timer++;
    for (int to : g[v]) {
        dfs(to, nh + 1);
    }
    tout[v] = timer++;
}

int ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int ans(int l, int r) {
    if (ch(r, l)) {
        return rh[l] - rh[r];
    } else {
        return -1;
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    bfs();
    string l;
    cin >> l;
    int len = (int)l.size();
    int v = 0;
    vector<int> go(len, -1);
    for (int i = 0; i < len; ++i) {
        v = bor[v].go[l[i] - 'a'];
        int u = v;
        while (u != 0) {
            if (bor[u].fl) {
                go[i - h[u] + 1] = i + 1;
            }
            u = bor[u].spl;
        }
    }
    for (int i = 0; i < len; ++i) {
        //cout << go[i] << " ";
        if (go[i] != -1) {
            g[go[i]].push_back(i);
        }
    }
    //cout << endl;
    for (int i = len; i >= 0; --i) {
        if (!us[i]) {
            dfs(i, 0);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << ans(l, r) << endl;
    }
    int k;
    cin >> k;
    for (int _ = 0; _ < k; ++_) {
        int t, a, b, c, d, e, nl, nr;
        cin >> t >> a >> b >> c >> d >> e >> nl >> nr;
        int sum = 0;
        for (int i = 0; i < t; ++i) {
            int rans = ans(min(nl % len, nr % len), max(nl % len, nr % len) + 1);
            nl = (a * nl + b) % e;
            nr = (c * nr + d + rans + e) % e;
            if (rans != -1) {
                sum = (sum + rans) % e;
            }
        }
        cout << sum << endl;
    }
    return 0;
}
