#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5 + 1;
vector<int> tree(4 * MAX), up_tree(4 * MAX);

void build(int v, int l, int r, vector<int> & a) {
    if (l + 1 == r) {
        tree[v] = a[l];
        up_tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m, r, a);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void push(int v) {
    int x = up_tree[v];
    up_tree[2 * v] += x;
    up_tree[2 * v + 1] += x;
    tree[2 * v] += x;
    tree[2 * v + 1] += x;
    up_tree[v] = 0;
}

void update(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] += 1;
        up_tree[v] += 1;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr);
    update(2 * v + 1, m, r, ql, qr);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 1e9;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    vector<vector<int>> u(n);
    vector<array<int, 3>> u2;
    vector<int> ch(n + 1);
    vector<int> l(m), r(m);
    vector<vector<int>> ch2(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> l[i] >> r[i];
        --l[i];
        ch[l[i]] -= 1;
        ch[r[i]] += 1;
        ch2[l[i]].push_back(i);
        ch2[r[i]].push_back(i);
    }
    int now = 0;
    vector<int> u3;
    for (int i = 0; i < n; ++i) {
        now += ch[i];
        a[i] += now;
        if (a[i] < 0) {
            u3.push_back(i);
        }
    }
    build(1, 0, n, a);
    int ans = 0;
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        for (int to : ch2[i]) {
            if (l[to] == i) {
                st.insert({-r[to], to});
            } else {
                st.erase({-r[to], to});
            }
        }
        int b = get(1, 0, n, i, i + 1);
        if (b >= 0) continue;
        for (int j = 0; j < abs(b); ++j) {
            auto [k, in] = (*st.begin());
            update(1, 0, n, l[in], r[in]);
            ans++;
            st.erase(st.begin());
        }
    }
    cout << ans << endl;
    /*for (int i = 0; i < m; ++i) {
        int sz = lower_bound(u3.begin(), u3.end(), r[i]) - u3.begin();
        sz -= lower_bound(u3.begin(), u3.end(), l[i]) - u3.begin();
        u2.push_back({-sz, l[i], r[i]});
    }
    sort(u2.begin(), u2.end());
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        auto [sz, ls, rs] = u2[i];
        int minm = get(1, 0, n, ls, rs);
        if (minm >= 0) {
            continue;
        }
        update(1, 0, n, ls, rs);
        ans++;
    }
    cout << ans << endl;*/
    return 0;
}
