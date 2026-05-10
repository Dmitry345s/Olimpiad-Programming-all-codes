#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 6e5 + 1;
vector<vector<int>> tree(2, vector<int> (4 * MAX));

void build(int v, int l, int r, int ch) {
    if (l + 1 == r) {
        tree[ch][v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, ch);
    build(2 * v + 1, m, r, ch);
    tree[ch][v] = tree[ch][2 * v] + tree[ch][2 * v + 1];
}

void update(int v, int l, int r, int ch, int id) {
    if (l + 1 == r) {
        tree[ch][v] += 1;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, ch, id);
    } else {
        update(2 * v + 1, m, r, ch, id);
    }
    tree[ch][v] = tree[ch][2 * v] + tree[ch][2 * v + 1];
}

int get(int v, int l, int r, int ch, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[ch][v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ch, ql, qr) + get(2 * v + 1, m, r, ch, ql, qr);
}

long long solve(vector<int> b, int n) {
    //cout << 0 << endl;
    build(1, 0, MAX, 0);
    build(1, 0, MAX, 1);
    int now = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        now += b[i];
        ans += get(1, 0, MAX, (i + 1) % 2, 0, now + 1 + n);
        if (i % 2 == 0 && now >= 0) {
            ans += 1;
        }
        update(1, 0, MAX, i % 2, now + n);
        //cout << tree[i % 2][1] << endl;
        //cout << b[i] << " " << i << " " << ans << endl;
    }
    return ans;
}

signed main() {
    int n, e;
    cin >> n >> e;
    vector<int> a(n);
    vector<int> b(n);
    long long to_ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < e) {
            b[i] = 1;
        } else {
            b[i] = -1;
        }
        to_ans += (n - i + 1) / 2;
    }
    //cout << to_ans << endl;
    long long ans = 0;
    ans += solve(b, n);
    for (int i = 0; i < n; ++i) {
        if (a[i] <= e) {
            b[i] = -1;
        } else {
            b[i] = 1;
        }
    }
    ans += solve(b, n);
    cout << to_ans - ans << endl;
    return 0;
}
