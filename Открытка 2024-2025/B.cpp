#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e5 + 1;
int last[MAX];
vector<pair<int, int>> lr[MAX];
vector<int> a[MAX];
vector<array<int, 3>> qs[MAX];
int ans[MAX];
int tree[MAX];

void add(int i, int x) {
    for (; i < MAX; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i = ((i & (i + 1)) - 1)) {
        ans += tree[i];
    }
    return ans;
}

void solve(int x) {
    vector<array<int, 3>> to_ans;
    for (int i = 0; i < (int)a[x].size(); ++i) {
        to_ans.push_back({lr[x][i].first, lr[x][i].second, -1});
    }
    for (auto t : qs[x]) {
        to_ans.push_back(t);
    }
    //cout << 0 << endl;
    int cnt = 0;
    sort(to_ans.begin(), to_ans.end());
    for (int i = 0; i < (int)to_ans.size(); ++i) {
        auto [l, r, t] = to_ans[i];
        if (t == -1) {
            add(r, 1);
            cnt++;
        } else {
            ans[t] = (cnt - get(r));
        }
    }
    //cout << 0 << endl;
    for (int i = 0; i < (int)to_ans.size(); ++i) {
        auto [l, r, t] = to_ans[i];
        if (t == -1) {
            add(r, -1);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, g;
    cin >> n >> m >> g;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int b;
            cin >> b;
            --b;
            a[i].push_back(b);
            lr[i].push_back({-1, n});
        }
    }
    fill(last, last + m, n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < (int)a[i].size(); ++j) {
            lr[i][j].second = last[a[i][j]];
            last[a[i][j]] = i;
        }
    }
    fill(last, last + m, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)a[i].size(); ++j) {
            lr[i][j].first = last[a[i][j]];
            last[a[i][j]] = i;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, p;
        cin >> l >> r >> p;
        --l; --r; --p;
        qs[p].push_back({l, r, i});
        //cout << i << endl;
    }
    for (int i = 0; i < n; ++i) {
        solve(i);
        //cout << i << endl;
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
