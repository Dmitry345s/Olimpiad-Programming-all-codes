#include<bits/stdc++.h>

using namespace std;

const int MAX = 8e5 + 20;
int n;
int tree[MAX];

void add(int i, int x) {
    for (; i < 2 * n + 20; i |= (i + 1)) {
        tree[i] += x;
    }
}

long long get(int i) {
    long long ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

long long rans = 0;

void solve(vector<int> in) {
    if (in.empty()) return;
    in.insert(in.begin(), -1);
    in.push_back(n);
    int u = (int)in.size() - 2;
    //fill(tree, tree + MAX, 0);
    add(n + 5, 1);
    for (int i = 1; i < (int)in.size() - 1; ++i) {
        int y = in[i];
        for (int j = y - 1; j > max(in[i - 1], y - u - 1); --j) {
            int cnt = -j - 1 + 2 * (i - 1);
            add(cnt + n + 5, 1);
        }
        add(-y - 1 + 2 * i + n + 5, 1);
        for (int j = y; j < min(in[i + 1], y + u + 1); ++j) {
            int cnt = -j - 1 + 2 * i;
            rans += get(cnt - 1 + n + 5);
        }
    }
    add(n + 5, -1);
    for (int i = 1; i < (int)in.size() - 1; ++i) {
        int y = in[i];
        for (int j = y - 1; j > max(in[i - 1], y - u - 1); --j) {
            int cnt = -j - 1 + 2 * (i - 1);
            add(cnt + n + 5, -1);
        }
        add(-y - 1 + 2 * i + n + 5, -1);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> n >> k;
    vector<int> a(n);
    vector<vector<int>> all(k);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        all[a[i]].push_back(i);
    }
    //solve(all[0]);
    for (auto val : all) {
        solve(val);
    }
    cout << rans << endl;
    return 0;
}
