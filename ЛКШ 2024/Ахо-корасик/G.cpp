#include<bits/stdc++.h>

using namespace std;

const int A = 26, MAX = 1e6 + 5;

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
//Node bor2[MAX];

int add(string s) {
    int v = 0;
    for (auto c : s) {
        int ch = c - 'a';
        if (bor[v].go[ch] == -1) {
            bor.push_back(Node());
            bor.back().p = ch;
            bor.back().pr = v;
            bor[v].go[ch] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch];
    }
    bor[v].fl = 1;
    return v;
}

vector<vector<int>> g(MAX);

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

vector<int> ord;
int wh[MAX];
int sz[MAX];

void dfs(int v = 0, int p = 0) {
    ord.push_back(v);
    wh[v] = (int)ord.size() - 1;
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
}

int tree[4 * MAX];

void update(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x);
    } else {
        update(2 * v + 1, m, r, in, x);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    //cout << sizeof(Node) << endl;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q, n;
    cin >> q >> n;
    vector<int> all(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        all[i] = add(s);
    }
    bfs();
    dfs();
    vector<int> used(n);
    for (int num = 0; num < n; ++num) {
        update(1, 0, MAX, wh[all[num]], 1);
        update(1, 0, MAX, wh[all[num]] + sz[all[num]], -1);
        used[num] ^= 1;
    }
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '-') {
            int num;
            cin >> num;
            num--;
            if (!used[num]) continue;
            update(1, 0, MAX, wh[all[num]], -1);
            update(1, 0, MAX, wh[all[num]] + sz[all[num]], 1);
            used[num] ^= 1;
        } else if (t == '+') {
            int num;
            cin >> num;
            num--;
            if (used[num]) continue;
            update(1, 0, MAX, wh[all[num]], 1);
            update(1, 0, MAX, wh[all[num]] + sz[all[num]], -1);
            used[num] ^= 1;
        } else {
            int v = 0;
            string s;
            cin >> s;
            long long ans = 0;
            for (auto c : s) {
                int ch = c - 'a';
                v = bor[v].go[ch];
                ans += get(1, 0, MAX, 0, wh[v] + 1);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
