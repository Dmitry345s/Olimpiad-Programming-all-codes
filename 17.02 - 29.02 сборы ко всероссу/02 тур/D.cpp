#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 250003;
vector<int> pref(MAX);
vector<int> tree(4 * MAX);
vector<int> update_tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = pref[l];
        update_tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    update_tree[v] = 0;
}

void push(int v) {
    int x = update_tree[v];
    update_tree[v] = 0;
    update_tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
    tree[2 * v] += x;
    tree[2 * v + 1] += x;
}

void update(int v, int l, int r, int ql, int qr, int d) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        update_tree[v] += d;
        tree[v] += d;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, d);
    update(2 * v + 1, m, r, ql, qr, d);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return 1e18;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    int g;
    cin >> g;
    int k, n;
    cin >> n >> k;
    vector<int> c(n);
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    if (g == 3) {
        pref[0] = c[0] - s[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + s[i - 1] + c[i] - s[i];
        }
        build(1, 0, n);
        vector<int> rans(n);
        int maxm = 1e18;
        for (int i = 0; i < n - 1; ++i) {
            rans[i] = get(1, 0, n, i + 1, n) - s[i];
            //cout << rans[i] << endl;
            maxm = min(maxm, rans[i]);
            update(1, 0, n, 0, n, -c[i]);
        }
        pref[n - 1] = c[n - 1] - s[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            pref[i] = pref[i + 1] + s[i + 1] + c[i] - s[i];
        }
        build(1, 0, n);
        for (int i = n - 1; i >= 1; --i) {
            rans[i] = min(rans[i], get(1, 0, n, 0, i) - s[i]);
            update(1, 0, n, 0, n, -c[i]);
        }
        cout << -maxm << endl;
        for (int i = 0; i < n; ++i) {
            cout << (rans[i] == maxm);
        }
    } else if (g == 0 || g == 1) {
        int ans = 1e18;
        vector<int> rans(n, 1e18);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (j - i + 1 < k) continue;
                vector<pair<int, int>> to_ans;
                int mans = 0;
                for (int l = i; l <= j; ++l) {
                    to_ans.push_back({-s[l], l});
                    mans += c[l];
                }
                sort(to_ans.begin(), to_ans.end());
                for (int l = 0; l < k; ++l) {
                    mans += to_ans[l].first;
                }
                for (int l = 0; l < k; ++l) {
                    rans[to_ans[l].second] = min(rans[to_ans[l].second], mans);
                }
                for (int l = k; l < to_ans.size(); ++l) {
                    if (to_ans[k - 1].first == to_ans[l].first) {
                        rans[to_ans[l].second] = min(rans[to_ans[l].second], mans);
                    }
                }
                ans = min(ans, mans);
            }
        }
        cout << -ans << endl;
        for (int i = 0; i < n; ++i) {
            cout << (rans[i] == ans);
        }
    }
}
