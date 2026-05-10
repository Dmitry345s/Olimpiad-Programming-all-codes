#include<bits/stdc++.h>

#define int long long

using namespace std;
const int INF = 1e9, MAX = 2e5 + 1;

pair<int, int> tree[4 * MAX];
int update_tree[4 * MAX];

void push(int v) {
    int x = update_tree[v];
    update_tree[v] = 0;
    update_tree[2 * v] += x;
    tree[2 * v].first += x;
    tree[2 * v].second += x;
    update_tree[2 * v + 1] += x;
    tree[2 * v + 1].first += x;
    tree[2 * v + 1].second += x;
}

void update (int v, int l, int r, int ql, int qr, int x) {
    if (ql >= r || l >= qr) return;
    if (ql <= l && r <= qr) {
        tree[v].first += x;
        tree[v].second += x;
        update_tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v].first = min(tree[2 * v].first, tree[2 * v + 1].first);
    tree[v].second = max(tree[2 * v].second, tree[2 * v + 1].second);
}

signed main() {
    int n;
    cin >> n;
    array<int, 2> now = {0, 0};
    int mx = -1;
    int in = -1;
    int mn = INF;
    int in2 = -1;
    for (int i = 0; i < n; ++i) {
        int c, s;
        cin >> c >> s;
        --s;
        now[s] += c;
        if (c > mx) {
            mx = c;
            in = s;
        }
        if (s == 0) {
            update(1, 0, n + 1, 0, c, -1);
        } else {
            update(1, 0, n + 1, 0, c, 1);
        }
        int fl = 0;
        if ((in ^ 1) == 0) {
            fl = (tree[1].first < 0);
        } else {
            fl = (tree[1].second > 0);
        }
        if (fl) {
            cout << "?" << endl;
        } else {
            if (in == 0) {
                cout << ">" << endl;
            } else {
                cout << "<" << endl;
            }
        }
    }
    return 0;
}

