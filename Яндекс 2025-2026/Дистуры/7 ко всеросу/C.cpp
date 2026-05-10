#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;
int tree[MAX];

void upd(int i, int x) {
    for (; i < MAX; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

int sum(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> st(n);
    for (int i = 0; i < n; ++i) st[i] = i;
    vector<vector<pair<int, int>>> qs(m);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int a, b, x;
            cin >> a >> b >> x;
            --a; --b; --x;
            qs[x].push_back({a, b});
        } else {
            int r, x;
            cin >> r >> x;
            --r;
            for (int i = 0; i < x; ++i) {
                for (auto [u, v] : qs[i]) {
                    swap(st[u], st[v]);
                }
                r = st[r];
                for (int j = (int)qs[i].size() - 1; j >= 0; --j) {
                    swap(st[qs[i][j].first], st[qs[i][j].second]);
                }
            }
            cout << r + 1 << endl;
        }
    }
    return 0;
}
