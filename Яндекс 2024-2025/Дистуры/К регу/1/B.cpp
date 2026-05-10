#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 5, INF = 2e9, LN = 18;
int tree[MAX][LN], tree2[MAX][LN];
int ls[MAX], rs[MAX];
int prec[MAX];


void build (int n) {
    for (int i = 0; i < n; ++i) {
        tree[i][0] = ls[i];
    }
    for (int j = 1; j < LN; ++j) {
        for (int i = 0; i < n; ++i) {
            tree[i][j] = tree[i][j - 1];
            int x = (i + (1 << (j - 1)));
            if (x < n) {
                tree[i][j] = max(tree[i][j], tree[x][j - 1]);
            }
        }
    }
}

int get(int ql, int qr) {
    int sz = (qr - ql);
    int ans = -1;
    ans = max(ans, tree[ql][prec[sz]]);
    ans = max(ans, tree[qr - (1 << prec[sz])][prec[sz]]);
    return ans;
}

void build2 (int n) {
    for (int i = 0; i < n; ++i) {
        tree2[i][0] = rs[i];
    }
    for (int j = 1; j < LN; ++j) {
        for (int i = 0; i < n; ++i) {
            tree2[i][j] = tree2[i][j - 1];
            int x = (i + (1 << (j - 1)));
            if (x < n) {
                tree2[i][j] = min(tree2[i][j], tree2[x][j - 1]);
            }
        }
    }
}

int get2(int ql, int qr) {
    int sz = (qr - ql);
    int ans = INF;
    ans = min(ans, tree2[ql][prec[sz]]);
    ans = min(ans, tree2[qr - (1 << prec[sz])][prec[sz]]);
    return ans;
}

int fin(int st, int x, int n) {
    int l = st - 1, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int a = get(st, m + 1);
        int b = get2(st, m + 1);
        if (max(0, b - a) < x) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    for (int i = 0; i < n; ++i) {
        cin >> ls[i] >> rs[i];
    }
    prec[1] = 0;
    prec[2] = 1;
    for (int i = 3; i < MAX; ++i) {
        prec[i] = prec[i / 2] + 1;
    }
    build(n);
    build2(n);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int a = fin(i, m1, n);
        int b = fin(i, m2 + 1, n);
        //cout << b << " " << a << endl;
        ans += a - b;
    }
    cout << ans << endl;
    return 0;
}
