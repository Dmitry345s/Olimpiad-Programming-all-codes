#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e6 + 1;
pair<int, int> sts[MAX];

pair<int, int> tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {sts[l].second, sts[l].first};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

const int INF = 2e9;

pair<int, int> get1(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return {INF, INF};
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return min(get1(2 * v, l, m, ql, qr), get1(2 * v + 1, m, r, ql, qr));
}

pair<int, int> get2(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return {INF, INF};
    }
    if (l + 1 == r) {
        if (tree[v].first <= x) {
            return {sts[l].first, sts[l].second};
        } else {
            return {INF, INF};
        }
    }
    if (ql <= l && r <= qr) {
        if (tree[v].first > x) return {INF, INF};
        pair<int, int> u;
        int m = (l + r) / 2;
        if (tree[2 * v].first <= x) {
            u = get2(2 * v, l, m, ql, qr, x);
        } else {
            u = get2(2 * v + 1, m, r, ql, qr, x);
        }
        return u;
    }
    int m = (l + r) / 2;
    return min(get2(2 * v, l, m, ql, qr, x), get2(2 * v + 1, m, r, ql, qr, x));
}

signed main() {
    int n, g, b, d;
    cin >> n >> g >> b >> d;
    for (int i = 0; i < n; ++i) {
        cin >> sts[i].first >> sts[i].second;
    }
    sort(sts, sts + n);
    build(1, 0, n);
    int now = 0;
    int tl = b;
    int cs = INF;
    if (sts[0].first == 0) {
        cs = sts[0].second;
    }
    int ans = 0;
    while (now < d) {
        if (ans >= d * INF) break;
        int x = upper_bound(sts, sts + n, pair<int, int>{now, INF}) - sts;
        pair<int, int> u = get2(1, 0, n, x, n, cs);
        //cout << tl << " " << now << endl;
        int nd = u.first;
        if (now + g >= nd) {
            int del = nd - now - tl;
            int dif = max(0ll, del) * cs;
            if (dif > 0 && cs == INF) {
                cout << -1 << endl;
                return 0;
            }
            ans += dif;
            tl = max(0ll, tl - (nd - now));
            now = u.first;
            cs = u.second;
        } else {
            int cn = now + g;
            if (cn >= d) {
                int del = d - now - tl;
                int dif = max(0ll, del) * cs;
                if (dif > 0 && cs == INF) {
                    cout << -1 << endl;
                    return 0;
                }
                ans += dif;
                break;
            }
            int y = upper_bound(sts, sts + n, pair<int, int>{cn, INF}) - sts;
            if (y == x) {
                cout << -1 << endl;
                return 0;
            }
            pair<int, int> u2 = get1(1, 0, n, x, y);
            int del = g - tl;
            int dif = max(0ll, del) * cs;
            if (dif > 0 && cs == INF) {
                cout << -1 << endl;
                return 0;
            }
            ans += dif;
            //cout << ans << endl;
            tl = max(0ll, g - (u2.second - now));
            now = u2.second;
            cs = u2.first;
        }
    }
    if (ans >= d * INF) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}
