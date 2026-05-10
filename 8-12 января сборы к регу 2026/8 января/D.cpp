#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 5;
vector<int> g[MAX];

pair<int, int> mrg(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first) return a;
    if (a.first < b.first) return b;
    return {a.first, a.second + b.second};
}

int c[MAX];
vector<int> rc;
int us[MAX];

void do_c(int v) {
    rc.push_back(v);
    us[v] = 1;
    for (int to : g[v]) {
        if (us[to] || !c[to]) continue;
        do_c(to);
    }
}

pair<int, int> rdp[MAX];
pair<int, int> prdp[MAX];

void dfs(int v) {
    us[v] = 1;
    rdp[v] = {0, 1};
    prdp[v] = {0, 1};
    vector<pair<int, int>> all;
    for (int to : g[v]) {
        if (us[to] || c[to]) continue;
        dfs(to);
        all.push_back({prdp[to].first, to});
        rdp[v] = mrg(rdp[v], rdp[to]);
    }
    if (all.empty()) return;
    sort(all.rbegin(), all.rend());
    prdp[v].first = all[0].first + 1;
    prdp[v].second = 0;
    for (auto [len, to] : all) {
        if (len == all[0].first) {
            prdp[v].second += prdp[to].second;
        }
    }
    rdp[v] = mrg(rdp[v], prdp[v]);
    if ((int)all.size() > 1) {
        int mx = all[0].first;
        int mx2 = all[1].first;
        int cnt1 = 0;
        int cnt2 = 0;
        int sum = 0;
        for (auto [len, to] : all) {
            if (len == mx) {
                cnt1 += prdp[to].second;
                sum -= prdp[to].second * prdp[to].second;
            }
            if (len == mx2) {
                cnt2 += prdp[to].second;
            }
        }
        if (mx == mx2) {
            rdp[v] = mrg(rdp[v], {2 * mx + 2, (cnt1 * cnt1 + sum) / 2});
        } else {
            rdp[v] = mrg(rdp[v], {mx + mx2 + 2, cnt1 * cnt2});
        }
    }
}

pair<int, int> tree[4 * MAX];

void update(int v, int l, int r, int in, pair<int, int> now) {
    if (l + 1 == r) {
        tree[v] = now;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, now);
    } else {
        update(2 * v + 1, m, r, in, now);
    }
    tree[v] = mrg(tree[2 * v], tree[2 * v + 1]);
}

pair<int, int> get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return {-2 * MAX, 0};
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    return mrg(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    //assert(n <= 10);
    vector<int> cnt(n);
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[a]++;
        cnt[b]++;
    }
    for (int i = 0; i < n; ++i) {
        st.insert({cnt[i], i});
    }
    while ((*st.begin()).first == 1) {
        auto [u, v] = *st.begin();
        st.erase(st.begin());
        for (auto to : g[v]) {
            st.erase({cnt[to], to});
            cnt[to]--;
            if (cnt[to] < 1) continue;
            st.insert({cnt[to], to});
        }
    }
    for (auto [y, v] : st) {
        c[v] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (c[i]) {
            do_c(i);
            break;
        }
    }
    fill(us, us + n, 0);
    pair<int, int> ans = {0, 0};
    for (int i = 0; i < n; ++i) {
        if (c[i]) {
            dfs(i);
            //cout << i << " " << rdp[i].first << " " << rdp[i].second << endl;
            ans = mrg(ans, rdp[i]);
        }
    }
    int k = (int)rc.size() / 2;
    for (int i = 0; i < k; ++i) {
        update(1, 0, k, i, {prdp[rc[i]].first - i, prdp[rc[i]].second});
    }
    for (int j = 0; j < (int)rc.size(); ++j) {
        int i = (j + k) % (int)rc.size();
        if (i == 0) {
            for (int tt = 0; tt < k; ++tt) {
                pair<int, int> to_up = get(1, 0, k, tt, tt + 1);
                update(1, 0, k, tt, {to_up.first + (int)rc.size(), to_up.second});
            }
        }
        pair<int, int> now = tree[1];
        now.first += prdp[rc[i]].first + i;
        now.second *= prdp[rc[i]].second;
        //cout << j << " " << i << " " << now.first << " " << now.second << endl;
        ans = mrg(ans, now);
        //cout << i << " " << j % k <<  " " << prdp[rc[i]].first << " " << prdp[rc[i]].second << endl;
        update(1, 0, k, j % k, {prdp[rc[i]].first - i, prdp[rc[i]].second});
    }
    //cout << ans.first << endl;
    //cout << ans.first << endl;
    cout << ans.second << endl;
    return 0;
}
