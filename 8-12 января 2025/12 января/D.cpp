#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")

#define int long long

using namespace std;

const int MAX = 5e5 + 5, INF = 2e18;
int a[MAX];
int pref[MAX];

struct Node {
    int mn, mx;
    Node(int y = 0, int z = 0) {
        mn = y;
        mx = z;
    }
};

Node operator+ (Node a, Node b) {
    Node c;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    return c;
}

Node tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = Node(pref[l], pref[l]);
        //cout << tree[v].mnpr << " " << tree[v].mnsf << endl;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return INF;
    }
    int m = (l + r) / 2;
    //cout << v << " " << tree[v].mn << endl;
    if (ql <= l && r <= qr) {
        if (tree[v].mn < x) {
            if (l + 1 == r) {
                return l;
            }
            int u = get(2 * v, l, m, ql, qr, x);
            //cout << u << " " << l << " " << r << endl;
            if (u == INF) {
                return get(2 * v + 1, m, r, ql, qr, x);
            }
            return u;
        } else {
            return INF;
        }
    }
    int u = get(2 * v, l, m, ql, qr, x);
    if (u == INF) {
        return get(2 * v + 1, m, r, ql, qr, x);
    }
    return u;
}

int get2(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return -1;
    }
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[v].mx > x) {
            if (l + 1 == r) {
                return l;
            }
            int u = get2(2 * v + 1, m, r, ql, qr, x);
            if (u == -1) {
                return get2(2 * v, l, m, ql, qr, x);
            }
            return u;
        } else {
            return -1;
        }
    }
    int u = get2(2 * v + 1, m, r, ql, qr, x);
    if (u == -1) {
        return get2(2 * v, l, m, ql, qr, x);
    }
    return u;
}

int tree2[MAX];

void upd(int i) {
    for ( ; i < MAX; i = (i | (i + 1))) {
        tree2[i]++;
    }
}

int gf(int i) {
    int ans = 0;
    for ( ;i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree2[i];
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    int t;
    cin >> t;
    if (t == 1) {
        build(1, 0, n + 1);
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l;
            int u1 = get(1, 0, n + 1, l, r + 1, pref[l]);
            int u2 = get2(1, 0, n + 1, l, r + 1, pref[r]);
            //cout << u1 << " " << u2 << endl;
            int ans = 0;
            if (u1 != INF) ans++;
            if (u2 != -1) ans++;
            if (u1 != INF && u2 != -1 && u1 > u2) ans--;
            cout << ans << endl;
        }
    } else if (t == 2) {
        build(1, 0, n + 1);
        vector<int> fs(n + 1), fs2(n + 1);
        vector<vector<int>> cnt(n + 2);
        for (int i = 0; i < n + 1; ++i) {
            fs[i] = get(1, 0, n + 1, i, n + 1, pref[i]);
            fs2[i] = get2(1, 0, n + 1, 0, i + 1, pref[i]);
            if (fs[i] == INF) {
                cnt[n + 1].push_back(i);
            } else {
                cnt[fs[i]].push_back(i);
            }
            //cout << fs[i] << " " << fs2[i] << endl;
        }
        if (n > 3000) {
            vector<int> ch1(n + 1), ch2(n + 1);
            int rans = n * (n + 1) / 2;
            for (int i = n; i >= 0; --i) {
                ch1[i] = gf(i);
                ch2[i] = n - i - ch1[i];
                upd(fs2[i] + 1);
                for (auto x : cnt[i]) {
                    rans += gf(x);
                    //cout << "# " << i << " " << x << " " << gf(x) << endl;
                }
                //cout << i << " " << ch1[i] << " " << ch2[i] << endl;
            }
            for (int i = 0; i < n + 1; ++i) {
                rans += ch2[i] * (int)cnt[i].size();
                rans -= ch1[i];
            }
            cout << rans << endl;
        } else {
            int rans = 0;
            for (int i = 0; i < n + 1; ++i) {
                for (int j = i + 1; j < n + 1; ++j) {
                    int u1 = fs[i];
                    if (fs[i] >= j) u1 = INF;
                    int u2 = fs2[j];
                    if (fs2[j] < i) u2 = -1;
                    int ans = 0;
                    if (u1 != INF) ans++;
                    if (u2 != -1) ans++;
                    if (u1 != INF && u2 != -1 && u1 > u2) ans--;
                    rans += ans;
                }
            }
            cout << rans << endl;
        }
    }
    return 0;
}
