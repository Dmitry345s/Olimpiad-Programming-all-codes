#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

struct Node {
    int ans[2];
    int wh[2];
    int l, r;
    int ans_ls[2][2];
    Node() {
        ans[0] = 0;
        ans[1] = 0;
        wh[0] = -1;
        wh[1] = -1;
        l = -1;
        r = -1;
        ans_ls[0][0] = 0;
        ans_ls[0][1] = 0;
        ans_ls[1][0] = 0;
        ans_ls[1][1] = 0;
    }
    Node(char c, int in) {
        if (c == '0') {
            ans[0] = 1;
            ans[1] = 0;
            wh[0] = 0;
            wh[1] = -1;
            l = in;
            r = in + 1;
            ans_ls[0][0] = 1;
            ans_ls[0][1] = 0;
            ans_ls[1][1] = 0;
            ans_ls[1][0] = 0;
        } else if (c == '1') {
            ans[0] = 0;
            ans[1] = 1;
            wh[0] = -1;
            wh[1] = 0;
            l = in;
            r = in + 1;
            ans_ls[0][0] = 0;
            ans_ls[0][1] = 0;
            ans_ls[1][0] = 0;
            ans_ls[1][1] = 1;
        } else {
            ans[0] = 1;
            ans[1] = 1;
            wh[0] = 0;
            wh[1] = 0;
            l = in;
            r = in + 1;
            ans_ls[0][0] = 1;
            ans_ls[0][1] = 1;
            ans_ls[1][0] = 1;
            ans_ls[1][1] = 1;
        }
    }
};

bool operator == (Node a, Node b) {
    return (a.l == b.l && a.r == b.r && a.ans[0] == b.ans[0] && a.ans[1] == b.ans[1] && a.wh[0] == b.wh[0] && a.wh[1] == b.wh[1] &&
            a.ans_ls[0][0] == b.ans_ls[0][0] && a.ans_ls[0][1] == b.ans_ls[0][1] && a.ans_ls[1][0] == b.ans_ls[1][0] && a.ans_ls[1][1] == b.ans_ls[1][1]);
}

const int MAX = 2e5;
char s[MAX];

Node operator + (Node a, Node b) {
    Node ans;
    ans.l = a.l;
    ans.r = b.r;
    if (b.wh[0] != -1) {
        ans.wh[0] = b.wh[0] + a.r - a.l;
    } else {
        ans.wh[0] = a.wh[0];
    }
    if (b.wh[1] != -1) {
        ans.wh[1] = b.wh[1] + a.r - a.l;
    } else {
        ans.wh[1] = a.wh[1];
    }
    int go[2][2];
    if (a.wh[0] == a.wh[1]) {
        go[0][0] = a.ans_ls[0][0];
        go[0][1] = a.ans_ls[0][1];
        go[1][0] = a.ans_ls[1][0];
        go[1][1] = a.ans_ls[1][1];
    } else if (a.wh[0] < a.wh[1]) {
        int t0 = a.ans_ls[0][0];
        int t1 = a.ans_ls[1][0];
        int dif = a.wh[1] - a.wh[0];
        if (a.wh[0] == -1) {
            t0 = 1;
        }
        go[0][0] = t0 + a.ans_ls[0][1] * dif;
        go[0][1] = a.ans_ls[0][1];
        go[1][0] = t1 + a.ans_ls[1][1] * dif;
        go[1][1] = a.ans_ls[1][1];
    } else {
        int t0 = a.ans_ls[0][1];
        int t1 = a.ans_ls[1][1];
        int dif = a.wh[0] - a.wh[1];
        if (a.wh[1] == -1) {
            t1 = 1;
        }
        go[0][0] = a.ans_ls[0][0];
        go[0][1] = t0 + a.ans_ls[0][0] * dif;
        go[1][0] = a.ans_ls[1][0];
        go[1][1] = t1 + a.ans_ls[1][0] * dif;
    }
    go[0][0] %= MOD;
    go[0][1] %= MOD;
    go[1][0] %= MOD;
    go[1][1] %= MOD;
    //cout << ans.l << " " << ans.r << " " << go[0][0] << " " << go[0][1] << " " << go[1][0] << " " << go[1][1] << endl;
    ans.ans[0] = b.ans[0] * go[0][0] + b.ans[1] * go[0][1] + a.ans[0];
    ans.ans[0] %= MOD;
    ans.ans[1] = b.ans[0] * go[1][0] + b.ans[1] * go[1][1] + a.ans[1];
    ans.ans[1] %= MOD;
    if (b.wh[0] == -1) {
        ans.ans_ls[0][0] = a.ans_ls[0][0];
        ans.ans_ls[1][0] = a.ans_ls[1][0];
    } else {
        ans.ans_ls[0][0] = b.ans_ls[0][0] * go[0][0] + b.ans_ls[1][0] * go[0][1];
        ans.ans_ls[1][0] = b.ans_ls[0][0] * go[1][0] + b.ans_ls[1][0] * go[1][1];
    }
    if (b.wh[1] == -1) {
        ans.ans_ls[0][1] = a.ans_ls[0][1];
        ans.ans_ls[1][1] = a.ans_ls[1][1];
    } else {
        ans.ans_ls[0][1] = b.ans_ls[0][1] * go[0][0] + b.ans_ls[1][1] * go[0][1];
        ans.ans_ls[1][1] = b.ans_ls[0][1] * go[1][0] + b.ans_ls[1][1] * go[1][1];
    }
    ans.ans_ls[0][0] %= MOD;
    ans.ans_ls[0][1] %= MOD;
    ans.ans_ls[1][0] %= MOD;
    ans.ans_ls[1][1] %= MOD;
    /*if (ans.wh[0] > 0 && s[ans.wh[0] + ans.l] == '?') {
        ans.ans_ls[0][0] += ans.ans_ls[0][1];
        ans.ans_ls[0][0] %= MOD;
        ans.ans_ls[0][1] = ans.ans_ls[0][0];

    }
    if (ans.wh[1] > 0 && s[ans.wh[1] + ans.l] == '?') {
        ans.ans_ls[1][0] += ans.ans_ls[1][1];
        ans.ans_ls[1][0] %= MOD;
        ans.ans_ls[1][1] = ans.ans_ls[1][0];
    }*/
    return ans;
}

Node tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = Node(s[l], l);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
    //cout << l << " " << r << " " << tree[v].ans[0] << " " << tree[v].ans[1] << endl;
}

void update(int v, int l, int r, int in, char c) {
    if (l + 1 == r) {
        tree[v] = Node(c, l);
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, c);
    } else {
        update(2 * v + 1, m, r, in, c);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int in;
        char c;
        cin >> in >> c;
        --in;
        s[in] = c;
        update(1, 0, n, in, c);
        cout << (tree[1].ans[0] + tree[1].ans[1]) % MOD << endl;
    }
    return 0;
}
