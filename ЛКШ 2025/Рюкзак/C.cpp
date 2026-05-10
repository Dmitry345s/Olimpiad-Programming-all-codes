#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e9, MAX = 3e5;
int n, nn;
int ta[MAX], tb[MAX];

int get(int i, int x) {
    if (x - i < 0 || x - i >= nn || i < 0 || i >= n) return -INF - 1;
    return ta[i] + tb[x - i];
}

vector<array<int, 3>> tree(1, {-1, -1, -1});

void add(int v, int l, int r, int in) {
    if (in == -1) return;
    //cout << v << " " << l << " " << r << endl;
    int m = (l + r) / 2;
    if (get(tree[v][0], m) < get(in, m)) {
        swap(tree[v][0], in);
    }
    //cout << "zvo " << v << " " << l << " " << r << " " << in << endl;
    if (l + 1 == r) return;
    if (get(in, l) >= get(tree[v][0], l) && get(in, r) <= get(tree[v][0], r)) {
        if (tree[v][1] == -1) {
            tree[v][1] = (int)tree.size();
            tree.push_back({-1, -1, -1});
        }
        add(tree[v][1], l, m, in);
    } else {
        if (tree[v][2] == -1) {
            tree[v][2] = (int)tree.size();
            tree.push_back({-1, -1, -1});
        }
        add(tree[v][2], m, r, in);
    }
}

int getl(int v, int l, int r, int x) {
    int m = (l + r) / 2;
    int ans = get(tree[v][0], x);
    //cout << "z " << v << " " << l << " " << r << " " << x << " " << ans << endl;
    if (x < m) {
        if (tree[v][1] != -1) {
            ans = max(ans, getl(tree[v][1], l, m, x));
        }
    } else {
        if (tree[v][2] != -1) {
            ans = max(ans, getl(tree[v][2], m, r, x));
        }
    }
    return ans;
}

vector<int> mx(vector<int> a, vector<int> b) {
    n = (int)a.size();
    nn = (int)b.size();
    for (int i = 0; i < n; ++i) {
        ta[i] = a[i];
        //cout << a[i] << " ";
    }
    //cout << endl;
    for (int i = 0; i < nn; ++i) {
        tb[i] = b[i];
        //cout << b[i] << " ";
    }
    //cout << endl;
    tree = {{-1, -1, -1}};
    for (int i = 0; i < n; ++i) {
        add(0, 0, n + nn - 1, i);
    }
    vector<int> ans(n + nn - 1);
    for (int i = 0; i < n + nn - 1; ++i) {
        ans[i] = getl(0, 0, n + nn - 1, i);
        //cout << ans[i] << " ";
    }
    /*for (int i = 0; i < n + nn - 1; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    cout << endl;*/
    return ans;
}

void to_solve(vector<int> & dp, vector<int> b, int w, int c) {
    //cout << w << " " << c << endl;
    b.resize((c + w - 1) / w);
    //cout << b[0] << endl;
    vector<int> pr((int)b.size() + 1);
    for (int i = 1; i <= (int)b.size(); ++i) {
        pr[i] = pr[i - 1] + b[i - 1];
    }
    for (int u = 0; u < w; ++u) {
        vector<int> a;
        for (int j = u; j < c + 1; j += w) {
            a.push_back(dp[j]);
        }
        a = mx(a, pr);
        for (int j = u; j < c + 1; j += w) {
            dp[j] = a[j / w];
        }
    }
    /*for (int i = 0; i < c + 1; ++i) {
        cout << dp[i] << " ";
    }
    cout << endl;*/
}

signed main() {
    int n, c;
    cin >> n >> c;
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        int w, v;
        cin >> w >> v;
        all.push_back({w, v});
    }
    sort(all.rbegin(), all.rend());
    vector<int> dp(c + 1, -INF);
    dp[0] = 0;
    int l = 0;
    while (l < n) {
        vector<int> now;
        int u = l;
        while (all[u].first == all[l].first) {
            now.push_back(all[l].second);
            l++;
        }
        to_solve(dp, now, all[u].first, c);
    }
    int ans = -INF;
    for (int i = 0; i <= c; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
