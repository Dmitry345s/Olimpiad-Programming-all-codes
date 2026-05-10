#include<bits/stdc++.h>

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

//# define int long long

using namespace std;
using ll = long long;

struct Node {
    int ls, rs;
    ll sum;
    Node(int ls = -1, int rs = -1, ll sum = 0) : ls(ls), rs(rs), sum(sum) {}
};

ll gt(int in, vector<Node> & tree) {
    if (in == -1) return 0;
    return tree[in].sum;
}

int build(int l, int r, vector<Node> & tree) {
    //cout << l << " " << r << endl;
    int ans = (int)tree.size();
    tree.push_back(Node());
    if (l + 1 == r) return ans;
    int m = (l + r) / 2;
    int left = build(l, m, tree), right = build(m, r, tree);
    tree[ans].ls = left; tree[ans].rs = right;
    tree[ans].sum = gt(tree[ans].ls, tree) + gt(tree[ans].rs, tree);
    return ans;
}

int update(int v, int l, int r, int in, int x, vector<Node> & tree) {
    int ans = (int)tree.size();
    tree.push_back(tree[v]);
    if (l + 1 == r) {
        tree[ans].sum += x;
        return ans;
    }
    int m = (l + r) / 2;
    if (in < m) {
        int u = update(tree[v].ls, l, m, in, x, tree);
        tree[ans].ls = u;
        tree[ans].sum = gt(tree[ans].ls, tree) + gt(tree[ans].rs, tree);
        return ans;
    }
    int u = update(tree[v].rs, m, r, in, x, tree);
    tree[ans].rs = u;
    tree[ans].sum = gt(tree[ans].ls, tree) + gt(tree[ans].rs, tree);
    return ans;
}

ll get(int v, int l, int r, int ql, int qr, vector<Node> & tree) {
    if (r <= ql || qr <= l) return 0;
    if (ql <= l && r <= qr) return tree[v].sum;
    int m = (l + r) / 2;
    ll lans = get(tree[v].ls, l, m, ql, qr, tree);
    ll rans = get(tree[v].rs, m, r, ql, qr, tree);
    return lans + rans;
}

const int MAX = 1e5 + 1, INF = 1e9 + 1;
const ll INF2 = 1e18;
vector<int> rts;
vector<Node> tree1;
vector<Node> tree2;
int _;
int n;

int getk(int l, int r, int k) {
    int nowl = 0, nowr = (int)rts.size();
    while (nowl + 1 < nowr) {
        int nowm = (nowl + nowr) / 2;
        int cntnow = get(rts[nowm], 0, n, l, r + 1, tree1);
        if (cntnow > k) {
            nowr = nowm;
        } else {
            nowl = nowm;
        }
    }
    return nowl;
}

ll getr(int l, int r) {
    int xk = getk(l, r, (r - l + 1));
    ll sum1 = get(rts[xk], 0, n, l, r + 1, tree2);
    ll sumall = get(rts.back(), 0, n, l, r + 1, tree2);
    return sumall - 2 * sum1;
}

void go(int l, int r, int optl, int optr, vector<ll> & was, vector<ll> & will) {
    if (l > r) return;
    int m = (l + r) / 2;
    int optm = optl;
    for (int i = optl; i <= min(m - 1, optr); ++i) {
        if (was[i] >= will[m]) continue;
        ll now = was[i] + getr(i + 1, m);
        if (now < will[m]) {
            will[m] = now;
            optm = i;
        }
    }
    go(l, m - 1, optl, optm, was, will);
    go(m + 1, r, optm, optr, was, will);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int k;
    cin >> n >> k;
    vector<array<int, 3>> ab(n);
    for (int i = 0; i < n; ++i) {
        cin >> ab[i][1] >> ab[i][2];
        if (ab[i][1] > ab[i][2]) swap(ab[i][1], ab[i][2]);
        ab[i][0] = (ab[i][1] + ab[i][2]);
    }
    sort(ab.begin(), ab.end());
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        all.push_back({ab[i][1], i});
        all.push_back({ab[i][2], i});
    }
    sort(all.begin(), all.end());
    rts.push_back(build(0, n, tree1));
    _ = build(0, n, tree2);
    for (auto [x, in] : all) {
        int uu = rts.back();
        rts.push_back(update(uu, 0, n, in, 1, tree1));
        _ = update(uu, 0, n, in, x, tree2);
    }
    vector<ll> dp(n, INF2);
    for (int i = 0; i < n; ++i) {
        dp[i] = getr(0, i);
    }
    for (int tt = 2; tt <= k; ++tt) {
        vector<ll> ndp(n, INF2);
        go(0, n - 1, 0, n - 1, dp, ndp);
        dp = ndp;
    }
    cout << dp[n - 1] << endl;
    return 0;
}
