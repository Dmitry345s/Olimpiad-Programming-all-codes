#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 2, LN = 20;

int tree[2][2 * MAX];

void upd(int i, int x, int ch) {
    for (int j = i; j < 2 * MAX; j = (j | (j + 1))) {
        tree[ch][j] += x;
    }
}

int get(int i, int ch) {
    int ans = 0;
    for (int j = i; j >= 0; j = (j & (j + 1)) - 1) {
        ans += tree[ch][j];
    }
    return ans;
}

vector<int> g[MAX];
int sz[MAX];
int ps[MAX];
int h[MAX];

void dfs(int v, int p) {
    sz[v] = 1;
    h[v] = h[p] + 1;
    for (int to : g[v]) {
        dfs(to, v);
        sz[v] += sz[to];
    }
}

bool cmp(int a, int b) {
    if (sz[a] == sz[b]) {
        return a < b;
    }
    return sz[a] < sz[b];
}

int tin[MAX], tout[MAX], hd[MAX];
int up[MAX][LN];
vector<int> ord;

void rdfs(int v, int num, int p) {
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    hd[v] = num;
    tin[v] = (int)ord.size();
    ord.push_back(v);
    int flag = 0;
    for (int to : g[v]) {
        if (!flag) {
            rdfs(to, num, v);
            flag = 1;
        } else {
            rdfs(to, to, v);
        }
    }
    tout[v] = (int)ord.size();
}

bool is_pr(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (is_pr(a, b)) return a;
    if (is_pr(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!is_pr(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int now1[MAX];
int now2[MAX];
vector<pair<int, int>> all1;
vector<pair<int, int>> all2;

void upd1(int in, int next) {
    int j = lower_bound(all1.begin(), all1.end(), pair<int, int> {now1[in], in}) - all1.begin();
    upd(j, -1, 0);
    now1[in] = next;
    j = lower_bound(all1.begin(), all1.end(), pair<int, int> {now1[in], in}) - all1.begin();
    upd(j, 1, 0);
}

void upd2(int in, int next) {
    int j = lower_bound(all2.begin(), all2.end(), pair<int, int> {now2[in], in}) - all2.begin();
    upd(j, -1, 1);
    now2[in] = next;
    j = lower_bound(all2.begin(), all2.end(), pair<int, int> {now2[in], in}) - all2.begin();
    upd(j, 1, 1);
}

int get1(int ql, int qr, int x) {
    int l = lower_bound(all1.begin(), all1.end(), pair<int, int> {x, ql}) - all1.begin();
    int r = upper_bound(all1.begin(), all1.end(), pair<int, int> {x, qr}) - all1.begin();
    --r;
    return get(r, 0) - get(l - 1, 0);
}

int get2(int ql, int qr, int x) {
    int l = lower_bound(all2.begin(), all2.end(), pair<int, int> {x, ql}) - all2.begin();
    int r = upper_bound(all2.begin(), all2.end(), pair<int, int> {x, qr}) - all2.begin();
    --r;
    return get(r, 1) - get(l - 1, 1);
}

void rupd(int a, int s) {
    upd1(tin[a], h[a] + s);
    upd2(tin[a], h[a] - s);
}

int rget(int a, int b) {
    int ans = 0;
    int x = lca(a, b);
    //cout << x << endl;
    int num1 = h[a];
    int num2 = h[x] - (h[a] - h[x]);
    while (!is_pr(hd[a], x)) {
        ans += get1(tin[hd[a]], tin[a], num1);
        a = ps[hd[a]];
    }
    ans += get1(tin[x], tin[a], num1);
    while (!is_pr(hd[b], x)) {
        ans += get2(tin[hd[b]], tin[b], num2);
        b = ps[hd[b]];
    }
    ans += get2(tin[x], tin[b], num2);
    return ans - (now1[tin[x]] == num1);
}

vector<int> solve(int n, int q, vector<int> a, vector<int> p, vector<int> qt, vector<int> qx, vector<int> qy) {
    int rt = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] == -1) {
            rt = i;
            ps[i] = i;
        } else {
            g[p[i]].push_back(i);
            ps[i] = p[i];
        }
    }
    h[rt] = -1;
    dfs(rt, rt);
    for (int i = 0; i < n; ++i) {
        sort(g[i].rbegin(), g[i].rend(), cmp);
    }
    rdfs(rt, rt, rt);
    for (int i = 0; i < n; ++i) {
        all1.push_back({h[ord[i]] + a[ord[i]], i});
        all2.push_back({h[ord[i]] - a[ord[i]], i});
    }
    for (int i = 0; i < q; ++i) {
        if (qt[i] == 1) {
            all1.push_back({h[qx[i]] + qy[i], tin[qx[i]]});
            all2.push_back({h[qx[i]] - qy[i], tin[qx[i]]});
        }
    }
    sort(all1.begin(), all1.end());
    sort(all2.begin(), all2.end());
    for (int i = 0; i < n; ++i) {
        now1[tin[i]] = h[i] + a[i];
        int j = lower_bound(all1.begin(), all1.end(), pair<int, int> {now1[tin[i]], tin[i]}) - all1.begin();
        upd(j, 1, 0);
        now2[tin[i]] = h[i] - a[i];
        j = lower_bound(all2.begin(), all2.end(), pair<int, int> {now2[tin[i]], tin[i]}) - all2.begin();
        upd(j, 1, 1);
    }
    vector<int> ans;
    for (int i = 0; i < q; ++i) {
        if (qt[i] == 1) {
            rupd(qx[i], qy[i]);
        } else {
            ans.push_back(rget(qx[i], qy[i]));
        }
    }
    return ans;
}

/*signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> p(n);
    vector<int> qt(q);
    vector<int> qx(q);
    vector<int> qy(q);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < q; ++i) cin >> qt[i] >> qx[i] >> qy[i];
    solve(n, q, a, p, qt, qx, qy);
}*/
