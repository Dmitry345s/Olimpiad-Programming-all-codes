#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

struct Node {
    int mn, in;
    int ps;
    Node() {
        mn = INF;
        in = -1;
        ps = 0;
    }
};

Node operator + (Node a, Node b) {
    Node ans;
    if (a.mn <= b.mn) {
        ans.mn = a.mn;
        ans.in = a.in;
    } else {
        ans.mn = b.mn;
        ans.in = b.in;
    }
    return ans;
}

const int MAX = 2e5 + 1;
Node tree[4 * MAX];

void push(int v) {
    int x = tree[v].ps;
    tree[v].ps = 0;
    tree[2 * v].ps += x;
    tree[2 * v].mn += x;
    tree[2 * v + 1].ps += x;
    tree[2 * v + 1].mn += x;
}

void build(int v, int l, int r, vector<int> & a) {
    if (l + 1 == r) {
        tree[v].mn = a[l];
        tree[v].in = l;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m, r, a);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree[v].mn += x;
        tree[v].ps += x;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

Node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return Node();
    if (ql <= l && r <= qr) return tree[v];
    push(v);
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

vector<array<int, 3>> all;

void solve(int l, int r, int n) {
    //cout << l << " " << r << endl;
    if (l + 1 > r) return;
    //cout << l << " " << r << endl;
    if (l + 1 == r) {
        int x = get(1, 0, n, l, r).mn;
        all.push_back({l, r, x});
        update(1, 0, n, l, r, INF);
        return;
    }
    int nowl = l;
    vector<int> ins;
    Node lsg = get(1, 0, n, l, r);
    int x = lsg.mn;
    while (nowl < r && lsg.mn == x) {
        int inn = lsg.in;
        ins.push_back(inn);
        nowl = inn + 1;
        if (nowl < r) {
            lsg = get(1, 0, n, nowl, r);
        }
    }
    update(1, 0, n, l, r, -x);
    for (auto in : ins) {
        update(1, 0, n, in, in + 1, INF);
    }
    all.push_back({l, r, x});
    int lsl = l;
    ins.push_back(r);
    for (int i = 0; i < (int)ins.size(); ++i) {
        //cout << l << " " << r << " " << ins[i] << endl;
        solve(lsl, ins[i], n);
        lsl = ins[i] + 1;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n, a);
    solve(0, n, n);
    /*for (auto [l, r, cnt] : all) {
        cout << l << " " << r << " " << cnt << endl;
    }*/
    vector<int> pref((int)all.size() + 1);
    for (int i = 0; i < (int)all.size(); ++i) {
        pref[i + 1] = pref[i] + all[i][2] * (all[i][1] - all[i][0]);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        int j = lower_bound(pref.begin(), pref.end(), x) - pref.begin();
        x -= pref[j - 1];
        auto [l, r, cnt] = all[j - 1];
        int len = r - l;
        x -= 1;
        x %= len;
        cout << l + x + 1 << endl;
    }
    return 0;
}

