#include<bits/stdc++.h>

using namespace std;

const int A = 26;
const int MAX = 1e5 + 1, INF = 1e9;

struct Node {
    int dp[A][A];
    Node(char c = '&') {
        for (int i = 0; i < A; ++i) {
            for (int j = 0; j < A; ++j) {
                dp[i][j] = INF;
            }
        }
        if (c != '&') {
            int y = c - 'a';
            for (int i = 0; i < A; ++i) {
                dp[i][i] = abs(y - i);
            }
        }
    }
    int get() {
        int ans = INF;
        for (int i = 0; i < A; ++i) {
            for (int j = 0; j < A; ++j) {
                ans = min(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

Node operator + (Node a, Node b) {
    Node ans;
    int rem[A][A];
    for (int s = 0; s < A; ++s) {
        rem[A - 1][s] = b.dp[A - 1][s];
        for (int f = A - 2; f >= 0; --f) {
            rem[f][s] = min(b.dp[f][s], rem[f + 1][s]);
        }
    }
    for (int f = 0; f < A; ++f) {
        for (int j = f; j < A; ++j) {
            for (int e = j; e < A; ++e) {
                ans.dp[f][e] = min(ans.dp[f][e], a.dp[f][j] + rem[j][e]);
            }
        }
    }
    return ans;
}

Node tree[3 * MAX];

void build(int v, int l, int r, string & s) {
    if (l + 1 == r) {
        tree[v] = Node(s[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, s);
    build(2 * v + 1, m, r, s);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int in, char c) {
    if (l + 1 == r) {
        tree[v] = Node(c);
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
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n = (int)s.size();
    build(1, 0, n, s);
    cout << tree[1].get() << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int in;
        char c;
        cin >> in >> c;
        --in;
        update(1, 0, n, in, c);
        cout << tree[1].get() << endl;
    }
    return 0;
}
