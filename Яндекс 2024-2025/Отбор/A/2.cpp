#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 5;
int a[MAX], p[MAX];
int t_ver[3 * MAX], pr[3 * MAX];
int t1[3 * MAX], sum[3 * MAX];
vector<pair<int, int>> ord;
int timer = -1;
pair<int, int> tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {p[l], a[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

pair<int, int> get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return {0, 0};
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

void to_max(int v, int l, int r, int ql, int qr, vector<int> & ans, int maxm) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (l + 1 == r) {
        if (tree[v].first == maxm) {
            ans.push_back(l);
        }
        return;
    }
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[2 * v].first == maxm) {
            to_max(2 * v, l, m, ql, qr, ans, maxm);
        }
        if (tree[2 * v + 1].first == maxm) {
            to_max(2 * v + 1, m, r, ql, qr, ans, maxm);
        }
        return;
    }
    to_max(2 * v, l, m, ql, qr, ans, maxm);
    to_max(2 * v + 1, m, r, ql, qr, ans, maxm);
}

vector<int> g[3 * MAX];

void to_get_tree(int l, int r, int n, int ps = -1) {
    if (l == r) return;
    timer++;
    pr[timer] = ps;
    if (ps != -1) {
        g[ps].push_back(timer);
    }
    auto [maxm, maxmmaxm] = get(1, 0, n, l, r);
    t1[timer] = maxm;
    ord.push_back({maxmmaxm, timer});
    sum[timer] = 0;
    t_ver[timer] = 1;
    vector<int> now_max;
    to_max(1, 0, n, l, r, now_max, maxm);
    int last = l;
    int pss = timer;
    for (int i = 0; i < (int)now_max.size(); ++i) {
        //cout << pss << " " << now_max[i] << endl;
        to_get_tree(last, now_max[i], n, pss);
        last = now_max[i] + 1;
    }
    to_get_tree(last, r, n, pss);
}

int get_ans(int v) {
    if (t_ver[v] == 1 || t_ver[v] == 0) {
        return t1[v];
    }
    return sum[v];
}

int get_rt(int v) {
    if (pr[v] == -1) return v;
    if (t_ver[pr[v]] != 2) return v;
    return pr[v] = get_rt(pr[v]);
}

void now_z(int v) {
    t_ver[v] = 0;
    sum[v] = 0;
    for (auto to : g[v]) {
        sum[v] += get_ans(to);
    }
    //cout << v << endl;
    //cout << v << " " << sum[v] << endl;
    while (sum[v] <= t1[v]) {
        //cout << v << " ";
        t_ver[v] = 2;
        int rt = get_rt(v);
        assert(t_ver[rt] == 2);
        int before = t1[rt];
        if (rt != v) {
            before = sum[rt];
            sum[rt] -= t1[v] - sum[v];
        }
        if (pr[rt] != -1 && t_ver[pr[rt]] == 0) {
            sum[pr[rt]] = (sum[pr[rt]] - before + sum[rt]);
            v = pr[rt];
        } else {
            break;
        }
    }
    //cout << endl;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    build(1, 0, n);
    to_get_tree(0, n, n);
    for (int i = 0; i <= timer; ++i) {
        //cout << pr[i] << endl;
    }
    //cout << '#' << endl;
    sort(ord.begin(), ord.end());
    int last = 0;
    long long ans = 0;
    for (int i = 0; i < (int)ord.size(); ++i) {
        //cout << i << " " << ord[i].first << " " << ord[i].second << endl;
        //cout << get_ans(0) << endl;
        ans += (ord[i].first - last) * get_ans(0);
        now_z(ord[i].second);
        //cout << t_ver[ord[i].second] << " " << sum[ord[i].second] << endl;
        last = ord[i].first;
    }
    cout << ans << endl;
    return 0;
}

/*5
10 9 10 5 4
3 4 3 10000 1*/
