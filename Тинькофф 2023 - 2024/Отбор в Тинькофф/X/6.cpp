#include<bits/stdc++.h>
#define int long long

using namespace std;

int MAX = 1e5, mod = 1e9 + 7;
vector<vector<int>> g(MAX);
vector<int> h(MAX), tin(MAX), sz(MAX), ord, sz2(MAX), c(MAX), h2(MAX), p(MAX, -1), leaves;
set<pair<int, int>> st;

void dfs(int v, int p = -1) {
    if (p != -1) {
        h[v] = h[p] + 1;
        h2[v] = h2[p] + c[p];
    }
    tin[v] = ord.size();
    ord.push_back(v);
    sz[v] = 1;
    sz2[v] = c[v];
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        sz2[v] += sz2[to];
    }
    int cnt = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (sz[to] >= (sz[v] + 1) / 2) {
            st.insert({min(v, to), max(v, to)});
            cnt++;
        }
    }
    if (!cnt) {
        leaves.push_back(v);
    }
}

vector<pair<int, int>> ins(MAX);
vector<int> last(MAX), cnts(MAX);
vector<vector<pair<int, int>>> trees(MAX);
vector<pair<int, int>> tree1(4 * MAX);

void getline(int v, int num) {
    int cnt = 0;
    while (p[v] != -1 && st.find({min(v, p[v]), max(v, p[v])}) != st.end()){
        ins[v] = {num, cnt};
        cnt++;
        v = p[v];
        cout << v << " ";
    }
    cout << endl;
    ins[v] = {num, cnt};
    cnt++;
    last[num] = v;
    cnts[num] = cnt;
    trees[num].resize(cnts[num] * 4);
}


void push(int v, int l, int r, vector<pair<int, int>> & tree) {
    int m = (l + r) / 2, d = tree[v].second;
    tree[2 * v + 1].second += d;
    tree[2 * v + 2].second += d;
    tree[2 * v + 1].first += d * (m - l);
    tree[2 * v + 2].first += d * (r - m);
    tree[v].second = 0;
}

void update(int v, int l, int r, int left, int right, int d, vector<pair<int, int>> & tree) {
    if (right <= l || r <= left) {
        return;
    }
    if (left <= l && r <= right) {
        tree[v].second += d;
        tree[v].first += d * (r - l);
        return;
    }
    push(v, l, r, tree);
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, left, right, d, tree);
    update(2 * v + 2, m, r, left, right, d, tree);
    tree[v].first = tree[2 * v + 1].first + tree[2 * v + 2].second;
}

int get(int v, int l, int r, int left, int right, vector<pair<int, int>> & tree) {
    if (right <= l || r <= left) {
        return 0;
    }
    if (left <= l && r <= right) {
        return tree[v].first;
    }
    push(v, l, r, tree);
    int m = (l + r) / 2;
    int sum1 = get(2 * v + 1, l, m, left, right, tree);
    int sum2 = get(2 * v + 2, m, r, left, right, tree);
    if (sum1 * sum2 == 0) {
        return sum1 + sum2;
    }
    return (sum1 + sum2) % mod;
}

int rget(int v) {
    int sum = 0;
    while (v != -1) {
        cout << v << endl;
        auto [i, j] = ins[v];
        sum = (sum + get(0, 0, cnts[i], j, cnts[i], trees[i])) % mod;
        cout << last[i] << endl;
        v = p[last[i]];
    }
    return sum;
}

void rupdate(int v, int d) {
    while (v != -1) {
        auto [i, j] = ins[v];
        update(0, 0, cnts[i], j, cnts[i], d, trees[i]);
        v = p[last[i]];
        cout << v << endl;
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        cin >> p[i];
        g[p[i]].push_back(i);
        g[i].push_back(p[i]);
    }
    //vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        //a[tin[i]] = c[i];
    }
    dfs(0);
    for (int i = 0; i < leaves.size(); ++i) {
        getline(leaves[i], i);
    }
    for (int i = 0; i < n; ++i) {
        cout << ins[i].first << " " << ins[i].second << " " << last[ins[i].first] << endl;
    }
    vector<int> ans(m + 1);
    ans[0] = c[n - 1];
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        int sum1 = rget(a), sum2 = get(0, 0, n, tin[a] + 1, tin[a] + sz[a], tree1);
        cout << sum1 << " " << sum2 << endl;
        int sum = (sum1 + sum2 + sz2[a] + h2[a]) % mod;
        cout << sum << endl;
        rupdate(b, sum);
        update(0, 0, n, tin[b] + 1, tin[b] + sz[b], sum, tree1);
        auto [j, l] = ins[n - 1];
        ans[i] = get(0, 0, cnts[j], l, l + 1, trees[j]) + get(0, 0, n, tin[n - 1], tin[n - 1] + 1, tree1) + c[n - 1];
    }
    for (int i = 0; i <= m; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
