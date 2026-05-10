#include<bits/stdc++.h>
#define int long long

using namespace std;

int mod = 998244353;

int MAX = 3e5;
vector<int> dp(MAX);
vector<int> pref(MAX + 1);
vector<int> tree(4 * MAX), update_tree(4 * MAX), tree2(4 * MAX), update_tree2(4 * MAX);
int z = 0;

void push(int v, int l, int r) {
    if (update_tree[v] == 0) return;
    int m = (l + r) / 2;
    int d = update_tree[v];
    tree[2 * v + 1] = (d * (pref[m - 1] - pref[max(l - 1, z)])) % mod;
    tree[2 * v + 2] = (d * (pref[r - 1] - pref[max(m - 1, z)])) % mod;
    update_tree[2 * v + 1] = d;
    update_tree[2 * v + 2] = d;
    update_tree[v] = 0;
}

void update(int v, int l, int r, int left, int right, int d) {
    if (right <= l || r <= left) {
        return;
    }
    if (left <= l && r <= right) {
        tree[v] = (d * (pref[r - 1] - pref[max(l - 1, z)])) % mod;
        update_tree[v] = d;
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, left, right, d);
    update(2 * v + 2, m, r, left, right, d);
    tree[v] = (tree[2 * v + 1] + tree[2 * v + 2]) % mod;
}

int get(int v, int l, int r, int left, int right) {
    if (right <= l || r <= left) {
        return 0;
    }
    if (left <= l && r <= right) {
        return tree[v];
    }
    push(v, l, r);
    int m = (l + r) / 2;
    return (get(2 * v + 1, l, m, left, right) + get(2 * v + 2, m, r, left, right)) % mod;
}

void push2(int v, int l, int r) {
    if (update_tree2[v] == 0) return;
    int m = (l + r) / 2;
    int d = update_tree2[v];
    tree2[2 * v + 1] = (d * (pref[m - 1] - pref[max(l - 1, z)])) % mod;
    tree2[2 * v + 2] = (d * (pref[r - 1] - pref[max(m - 1, z)])) % mod;
    update_tree2[2 * v + 1] = d;
    update_tree2[2 * v + 2] = d;
    update_tree2[v] = 0;
}

void update2(int v, int l, int r, int left, int right, int d) {
    if (right <= l || r <= left) {
        return;
    }
    if (left <= l && r <= right) {
        tree2[v] = (d * (pref[r - 1] - pref[max(l - 1, z)])) % mod;
        update_tree2[v] = d;
        return;
    }
    push2(v, l, r);
    int m = (l + r) / 2;
    update2(2 * v + 1, l, m, left, right, d);
    update2(2 * v + 2, m, r, left, right, d);
    tree2[v] = (tree2[2 * v + 1] + tree2[2 * v + 2]) % mod;
}

int get2(int v, int l, int r, int left, int right) {
    if (right <= l || r <= left) {
        return 0;
    }
    if (left <= l && r <= right) {
        return tree2[v];
    }
    push2(v, l, r);
    int m = (l + r) / 2;
    return (get2(2 * v + 1, l, m, left, right) + get2(2 * v + 2, m, r, left, right)) % mod;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    set<pair<int, int>> minm, maxm;
    dp[0] = 0;
    pref[0] = 0;
    pref[1] = dp[0];
    minm.insert({a[0], 0});
    update(0, 0, n, 0, 1, a[0]);
    maxm.insert({-a[0], 0});
    update2(0, 0, n, 0, 1, a[0]);
    for (int i = 1; i < n; ++i) {
        auto it = minm.upper_bound({a[i], 1e9}), it2 = maxm.upper_bound({-a[i], 1e9});
        if (it != minm.end()) {
            auto [num, in] = *it;
            while (it != minm.end()) {
                minm.erase(it);
                it = minm.upper_bound({a[i], 1e9});
            }
            minm.insert({a[i], in});
            update(0, 0, n, in, i, a[i]);
        } else {
            minm.insert({a[i], i});
        }
        if (it2 != maxm.end()) {
            auto [num, in] = *it2;
            while (it2 != maxm.end()) {
                maxm.erase(it2);
                it2 = maxm.upper_bound({-a[i], 1e9});
            }
            maxm.insert({-a[i], in});
            update2(0, 0, n, in, i, a[i]);
        } else {
            maxm.insert({-a[i], i});
        }
        auto it3 = (*minm.begin()).first, it4 = (*maxm.begin()).first;
        dp[i] = (get2(0, 0, n, 0, i) - get(0, 0, n, 0, i)) % mod;
        dp[i] = (dp[i] + mod) % mod;
        dp[i] -= (it3 + it4);
        dp[i] %= mod;
        pref[i + 1] = (pref[i] + dp[i]) % mod;
        update(0, 0, n, i, i + 1, a[i]);
        update2(0, 0, n, i, i + 1, a[i]);
    }
    cout << dp[n - 1] << endl;
    return 0;
}
