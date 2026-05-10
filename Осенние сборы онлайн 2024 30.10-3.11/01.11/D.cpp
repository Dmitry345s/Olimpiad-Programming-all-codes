#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 2;

int ch(long double dist, int a, int b) {
    if (dist >= a + b) {
        if (dist == a + b) return 4;
        return 0;
    }
    if (dist + a <= b) {
        if (dist + a == b) return 5;
        return 1;
    }
    if (dist + b <= a) {
        if (dist + b == a) return 6;
        return 2;
    }
    return 3;
}

int bin1(long double dist, vector<int> & b, int a) {
    int l = -1, r = (int)b.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int x = ch(dist, a, b[m]);
        if (x == 0 || x == 2) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int bin2(long double dist, vector<int> & b, int a) {
    int l = -1, r = (int)b.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int x = ch(dist, a, b[m]);
        if (x == 1) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int tree[4 * MAX], update_tree[4 * MAX];

void push(int v, int l, int r) {
    int x = update_tree[v];
    if (x == 0) return;
    int m = (l + r) / 2;
    tree[2 * v] = (m - l);
    tree[2 * v + 1] = (r - m);
    update_tree[2 * v] = 1;
    update_tree[2 * v + 1] = 1;
    update_tree[v] = 0;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        update_tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = 0;
    update_tree[v] = 0;
}

void update(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] = (r - l);
        update_tree[v] = 1;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    update(2 * v, l, m, ql, qr);
    update(2 * v + 1, m, r, ql, qr);
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
    push(v, l, r);
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int x1, y1;
    cin >> x1 >> y1;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int x2, y2;
    cin >> x2 >> y2;
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    long double dist = sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    //cout << dist << endl;
    //cout << dist << endl;
    build(1, 0, m);
    int rans = n + m;
    for (int i = 0; i < n; ++i) {
        int l = bin1(dist, b, a[i]);
        l++;
        int r = bin2(dist, b, a[i]);
        //cout << l << " " << r << endl;
        int x = (ch(dist, a[i], b[l]) != 3), y = (ch(dist, a[i], b[r - 1]) != 3);
        //cout << x << " " << y << endl;
        if (r - l >= 2) {
            rans += (r - l - x - y);
            rans += get(1, 0, m, l + 1, r);
            //cout << get(1, 0, m, l + 1, r) << endl;
            update(1, 0, m, l + 1, r);
            //cout << l + 1 << " " << r << endl;
        } else if (r - l == 1) {
            rans += (r - l - x);
        }
    }
    cout << rans << endl;
    /*int ans = n + m;
    vector<int> cnt(m);
    vector<int> cnt2(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (ch(dist, a[i], b[j]) == 3 || ch(dist, a[i], b[j]) == 5) {
                cnt[j]++;
                if (ch(dist, a[i], b[j]) == 5) ans--;
                if (j > 0 && ch(dist, a[i], b[j - 1]) >= 3) {
                    if (cnt2[j]) {
                        cnt[j]++;
                    }
                    cnt2[j]++;
                }
            }
        }
    }
    for (int i = m - 1; i >= 0; --i) {
        ans += cnt[i];
        //cout << cnt[i] << " ";
    }
    //cout << endl;
    cout << ans << endl;*/
    return 0;
}

/*0 0
2 1 2
4 0
5 2 3 4 5 6*/
