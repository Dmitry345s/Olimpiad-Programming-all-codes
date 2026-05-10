#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<int> p(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<array<int, 3>> qs(q);
    for (int i = 0; i < q; ++i) {
        string t;
        cin >> t;
        if (t == "ask") {
            qs[i][0] = 0;
        } else {
            qs[i][0] = 1;
        }
        cin >> qs[i][1] >> qs[i][2];
        --qs[i][1]; --qs[i][2];
    }
    reverse(qs.begin(), qs.end());
    vector<string> ans;
    for (int i = 0; i < q; ++i) {
        if (qs[i][0]) {
            if (root(qs[i][1]) == root(qs[i][2])) continue;
            p[root(qs[i][1])] = root(qs[i][2]);
        } else {
            if (root(qs[i][1]) != root(qs[i][2])) {
                ans.push_back("NO");
            } else {
                ans.push_back("YES");
            }
        }
    }
    for (int i = (int)ans.size() - 1; i >= 0; --i) {
        cout << ans[i] << endl;
    }
    return 0;
}
