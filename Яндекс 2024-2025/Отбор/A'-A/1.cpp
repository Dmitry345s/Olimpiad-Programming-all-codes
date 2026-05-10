#include<bits/stdc++.h>

using namespace std;

const int LN = 20;

void update(int in, int x, vector<int> & tree) {
    int v = in + (1 << (LN - 1));
    tree[v] = max(tree[v], x);
    while (v != 1) {
        v /= 2;
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
}

int get(int l, int r, vector<int> & tree) {
    l = l + (1 << (LN - 1));
    r += (1 << (LN - 1));
    int rans = 0, lans = 0;
    while (l < r) {
        if (l % 2 == 1) {
            lans = max(lans, tree[l]);
        }
        l = (l + 1) / 2;
        if (r % 2 == 0) {
            rans = max(rans, tree[r]);
        }
        r = (r - 1) / 2;
    }
    if (l == r) {
        lans = max(lans, tree[l]);
    }
    return max(lans, rans);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<int> cnt((int)b.size());
    for (int i = 1; i < (int)cnt.size(); ++i) {
        if (b[i] > b[i - 1] + 1) {
            cnt[i] = 1;
        }
    }
    vector<int> pref((int)cnt.size());
    for (int i = 0; i < (int)cnt.size(); ++i) {
        pref[i] = cnt[i];
        if (i > 0) pref[i] += pref[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        a[i] = j + 2 + pref[j];
    }
    a.push_back((1 << (LN - 1)) + 2);
    vector<vector<int>> trees(2, vector<int> (1 << LN));
    int last = 0;
    for (int i = 0; i < n; ++i) {
        //cout << a[i] << endl;
        if (last) update(a[i], last + 1, trees[1]);
        last = get(0, a[i + 1] - 2, trees[0]);
        update(a[i], get(0, a[i] - 1, trees[0]) + 1, trees[0]);
        int now1 = get(0, a[i] - 1, trees[1]);
        if (now1) update(a[i], now1 + 1, trees[1]);
    }
    vector<int> tree_to_ch(1 << LN);
    for (int i = 1; i < n; ++i) {
        update(a[i], get(0, a[i] - 1, tree_to_ch) + 1, tree_to_ch);
    }
    int flag = (get(0, (1 << (LN - 1)), trees[0]) == get(0, (1 << (LN - 1)), trees[1]));
    cout << max(get(0, (1 << (LN - 1)), tree_to_ch) + 1, max(last + 1, get(0, (1 << (LN - 1)), trees[0]) + flag)) << endl;
    return 0;
}
