#include<bits/stdc++.h>

using namespace std;

const int MAX = 35000;
const int MAX2 = 15000;

pair<int, bitset<2 * MAX2>> tree[2 * MAX];

pair<int, bitset<2 * MAX2>> mrg(pair<int, bitset<2 * MAX2>> a, pair<int, bitset<2 * MAX2>> b) {
    pair<int, bitset<2 * MAX2>> ans;
    if (a.first > b.first) {
        ans = a;
    } else if (b.first > a.first) {
        ans = b;
    } else {
        ans.first = a.first;
        ans.second = (a.second | b.second);
    }
    return ans;
}

bitset<2 * MAX2> em;

void build(int n) {
    for (int i = 0; i < 2 * n; ++i) {
        tree[i] = {0, em};
    }
}

pair<int, bitset<2 * MAX2>> get(int n, int l, int r) {
    pair<int, bitset<2 * MAX2>> ans = {0, em};
    l += n;
    r += n;
    while (l < r) {
        if (l % 2) {
            ans = mrg(ans, tree[l]);
            l += 1;
        }
        if (r % 2) {
            ans = mrg(ans, tree[r - 1]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

void upd(int n, int in, pair<int, bitset<2 * MAX2>> now) {
    int v = in + n;
    tree[v] = mrg(tree[v], now);
    while (v > 1) {
        v /= 2;
        tree[v] = mrg(tree[2 * v], tree[2 * v + 1]);
    }
}

signed main() {
    int n;
    cin >> n;
    vector<array<int, 3>> all(n);
    for (int i = 0; i < n; ++i) cin >> all[i][0] >> all[i][1] >> all[i][2];
    sort(all.begin(), all.end());
    vector<int> y(n);
    vector<int> cl(n);
    for (int i = 0; i < n; ++i) {
        y[i] = all[i][1];
        y[i]--;
        cl[i] = all[i][2];
    }
    em[MAX2] = 1;
    build(n);
    for (int i = 0; i < n; ++i) {
        pair<int, bitset<2 * MAX2>> now = get(n, 0, y[i] + 1);
        now.first += 1;
        if (cl[i] == 1) {
            now.second = (now.second << 1);
        } else {
            now.second = (now.second >> 1);
        }
        upd(n, y[i], now);
    }
    pair<int, bitset<2 * MAX2>> t_ans = {0, em};
    for (int i = 0; i < n; ++i) {
        auto u = get(n, i, i + 1);
        t_ans = mrg(t_ans, u);
    }
    int ans = n + 1;
    for (int i = 0; i < 2 * MAX2; ++i) {
        if (t_ans.second[i]) {
            int tr = i - MAX2;
            ans = min(ans, abs(tr));
        }
    }
    cout << t_ans.first << " " << ans << endl;
    return 0;
}
