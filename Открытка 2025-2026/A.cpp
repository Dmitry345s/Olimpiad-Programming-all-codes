#include<bits/stdc++.h>

//#define int long long

using namespace std;

const int MAX = 2e5 + 2;
int tr[MAX];
int tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = tr[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return MAX;
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    unordered_map<int, int> mp1, mp2, mp3, mp4;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    for (int i = n - 1; i >= 0; --i) {
        int d1 = all[i].first;
        int d2 = all[i].second;
        int d3 = all[i].first + all[i].second;
        int d4 = all[i].first - all[i].second;
        tr[i] = n + 1;
        if (mp1.find(d1) != mp1.end()) {
            tr[i] = min(tr[i], mp1[d1]);
        }
        mp1[d1] = i;
        if (mp2.find(d2) != mp2.end()) {
            tr[i] = min(tr[i], mp2[d2]);
        }
        mp2[d2] = i;
        if (mp3.find(d3) != mp3.end()) {
            tr[i] = min(tr[i], mp3[d3]);
        }
        mp3[d3] = i;
        if (mp4.find(d4) != mp4.end()) {
            tr[i] = min(tr[i], mp4[d4]);
        }
        mp4[d4] = i;
    }
    build(1, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        int x = get(1, 0, n, l, r);
        if (x < r) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
