#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("function-in-line")
//#define int long long

using namespace std;

const int MOD = 1e9 + 7, MAX = 1e5 + 5, K = 500 + 5;
int k;
vector<int> ans[MAX];
int p[MAX], max_edge[MAX], cnt[MAX], sz[MAX];

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

int mod(int x) {
    if (x >= MOD) return x - MOD;
    return x;
}

void unite(int a, int b, int len) {
    if (sz[a] > sz[b]) {
        swap(a, b);
    }
    if (max_edge[a] < len) {
        max_edge[a] = len;
        if (cnt[a] + 1 <= k) {
            ans[a][cnt[a] + 1]--;
        }
        ans[a][1]++;
        cnt[a] = 0;
    }
    if (max_edge[b] < len) {
        max_edge[b] = len;
        if (cnt[b] + 1 <= k) {
            ans[b][cnt[b] + 1]--;
        }
        ans[b][1]++;
        cnt[b] = 0;
    }
    int cnt1 = cnt[a] + cnt[b];
    p[a] = b;
    max_edge[b] = len;
    cnt[b] = 1 + cnt1;
    sz[b] += sz[a];
    vector<int> new_ans(k + 1);
    //cout << sz[a] << endl;
    for (int sum = 0; sum <= min(k, sz[b]); ++sum) {
        for (int j = 0; j <= min(sum, sz[a]); ++j) {
            //cout << ans[a][j] << " " << ans[b][sum - j] << endl;
            new_ans[sum] = mod(new_ans[sum] + (1ll * ans[a][j] * ans[b][sum - j]) % MOD);
        }
        //cout << new_ans[sum] << endl;
    }
    //cout << endl;
    ans[b] = new_ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m >> k;
    vector<array<int, 3>> edge(m);
    for (int i = 0; i < m; ++i) {
        cin >> edge[i][1] >> edge[i][2] >> edge[i][0];
    }
    for (int i = 2; i <= n; ++i) {
        edge.push_back({(int)2e9, 1, i});
    }
    sort(edge.begin(), edge.end());
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        ans[i].resize(K);
        ans[i][0] = 1;
        ans[i][1] = 1;
        sz[i] = 1;
        max_edge[i] = 0;
        cnt[i] = 0;
    }
    for (auto [len, a, b] : edge) {
        if (root(a) == root(b)) continue;
        ////cout << root(a) << " " << root(b) << " " << len << endl;
        unite(root(a), root(b), len);
    }
    set<int> now;
    for (int i = 1; i <= n; ++i) {
        now.insert(root(i));
    }
    int rans = 1;
    for (int to : now) {
        //cout << to << endl;
        if (cnt[to] + 1 > k && max_edge[to] != 2e9) {
            ans[to][1]++;
        }
        int cnt_now = 0;
        for (int i = 0; i <= k; ++i) {
            cnt_now = (cnt_now + ans[to][i]) % MOD;
        }
        rans = (1ll * rans * cnt_now) % MOD;
    }
    cout << rans << endl;
    assert(rans < MOD);
    return 0;
}
