#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e5;
vector<int> tree(4 * MAX);
vector<int> update_tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        update_tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    update_tree[v] = 0;
    tree[v] = 0;
}

void push(int v) {
    int x = update_tree[v];
    tree[2 * v] += x;
    tree[2 * v + 1] += x;
    update_tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
    update_tree[v] = 0;
}

void update1(int v, int l, int r, int id, int num) {
    if (l + 1 == r) {
        tree[v] = num;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    if (id < m) {
        update1(2 * v, l, m, id, num);
    } else {
        update1(2 * v + 1, m, r, id, num);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void update2(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] += 1;
        update_tree[v] += 1;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update2(2 * v, l, m, ql, qr);
    update2(2 * v + 1, m, r, ql, qr);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int solve(int n, int m, int k, vector<int> c1, vector<int> c2) {
    build(1, 0, n);
    vector<int> all(n);
    for (int i = 0; i < k; ++i) {
        all[c2[i]] = 1;
    }
    for (int i = 0; i < m; ++i) {
        all[c1[i]] = 2;
    }
    set<array<int, 3>> st;
    int last = -1e9;
    for (int i = 0; i < n; ++i) {
        if (all[i] == 0) {
            update1(1, 0, n, i, -1e9);
        } else if (all[i] == 1) {
            update1(1, 0, n, i, i - last);
            int j = upper_bound(c1.begin(), c1.end(), i) - c1.begin();
            if (j == (int)c1.size()) {
                st.insert({(int)1e9, 1, i});
            } else {
                st.insert({c1[j] - i, 1, i});
            }
        } else {
            update1(1, 0, n, i, -1e9);
            int j = lower_bound(c1.begin(), c1.end(), i) - c1.begin();
            st.insert({i - j, 2, j});
            last = i;
        }
    }
    //cout << 0 << endl;
    int now = 0;
    int ans = 1e9;
    //cout << tree[1] << endl;
    for (int i = 0; i < n; ++i) {
        int jhg = 0;
        while (!st.empty() && (*(st.begin()))[0] == i) {
            auto [t, tp, in] = *st.begin();
            //cout << t << " " << tp << " " << in << endl;
            if (tp == 2) {
                jhg++;
            } else {
                update1(1, 0, n, in, -1e9);
                //cout << tree[1] << endl;
            }
            st.erase(st.begin());
        }
        if (i != 0 && now < m) {
            update2(1, 0, n, c1[now] - i, n);
        }
        now += jhg;
        ans = min(ans, i + max(0ll, tree[1]));
    }
    return ans;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c1(m), c2(k), c3(m), c4(k);
    for (int i = 0; i < m; ++i) {
        cin >> c1[i];
        c1[i]--;
        c3[m - 1 - i] = n - 1 - c1[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> c2[i];
        c2[i]--;
        c4[k - 1 - i] = n - 1 - c2[i];
    }
    //cout << solve(n, m, k, c1, c2) << endl;
    cout << min(solve(n, m, k, c1, c2), solve(n, m, k, c3, c4)) << endl;
    return 0;
}
