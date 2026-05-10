#include<bits/stdc++.h>

//#define int long long

using namespace std;

void build(int v, int l, int r, vector<int> & tree, vector<int> & update_tree, vector<int> & a) {
    if (l + 1 == r) {
        tree[v] = a[l];
        update_tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, tree, update_tree, a);
    build(2 * v + 1, m, r, tree, update_tree, a);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    update_tree[v] = 0;
}

void push(int v, vector<int> & tree, vector<int> & update_tree) {
    int x = update_tree[v];
    update_tree[v] = 0;
    update_tree[2 * v] += x;
    tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
    tree[2 * v + 1] += x;
}

void update(int v, int l, int r, int ql, int qr, int x, vector<int> & tree, vector<int> & update_tree) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree[v] += x;
        update_tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    push(v, tree, update_tree);
    update(2 * v, l, m, ql, qr, x, tree, update_tree);
    update(2 * v + 1, m, r, ql, qr, x, tree, update_tree);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

const int INF = 2e9;

int get(int v, int l, int r, int ql, int qr, vector<int> & tree, vector<int> & update_tree) {
    if (qr <= l || r <= ql) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    push(v, tree, update_tree);
    return min(get(2 * v, l, m, ql, qr, tree, update_tree), get(2 * v + 1, m, r, ql, qr, tree, update_tree));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    map<int, vector<int>> mp;
    vector<int> all;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        mp[c].push_back(b);
        all.push_back(c);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int r = 0;
    vector<int> cnt(n);
    int cnt2 = n - 1;
    vector<pair<int, int>> now;
    for (int l = 0; l < (int)all.size(); ++l) {
        while (r < (int)all.size() && cnt2 > 0) {
            for (int v : mp[all[r]]) {
                cnt[v]++;
                if (cnt[v] == 1) cnt2--;
            }
            r++;
        }
        if (cnt2 == 0) {
            while (!now.empty() && now.back().second == all[r - 1]) {
                now.pop_back();
            }
            now.push_back({all[l], all[r - 1]});
            //cout << all[l] << " " << all[r - 1] << endl;
        }
        for (int v : mp[all[l]]) {
            cnt[v]--;
            if (cnt[v] == 0) cnt2++;
        }
    }
    sort(now.begin(), now.end());
    int nn = (int)now.size();
    vector<int> ls, rs;
    for (int i = 0; i < (int)now.size(); ++i) {
        ls.push_back(now[i].first);
        rs.push_back(now[i].second);
    }
    vector<int> nt[2][2];
    vector<int> nut[2][2];
    vector<int> a[2][2];
    for (int i = 0; i < nn; ++i) {
        //cout << i << endl;
        a[0][0].push_back(0);
        a[1][0].push_back(-now[i].first);
        a[0][1].push_back(now[i].second);
        a[1][1].push_back(a[0][1][i] + a[1][0][i]);
    }
    //cout << nn << endl;
    if (nn > 0) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                nt[i][j].assign(4 * nn + 4, 0);
                nut[i][j].assign(4 * nn + 4, 0);
                build(1, 0, nn, nt[i][j], nut[i][j], a[i][j]);
            }
        }
    }
    //cout << -2 << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int li, ri, x;
        cin >> li >> ri >> x;
        if (nn == 0) {
            cout << "No" << endl;
            continue;
        }
        int j1 = lower_bound(ls.begin(), ls.end(), li) - ls.begin();
        int j2 = upper_bound(rs.begin(), rs.end(), ri) - rs.begin();
        int minm = INF;
        if (j2 < j1) {
            update(1, 0, nn, j2, j1, li - ri, nt[1][1], nut[1][1]);
            int y1 = get(1, 0, nn, j2, j1, nt[1][1], nut[1][1]);
            minm = min(minm, y1);
            update(1, 0, nn, j2, j1, -li + ri, nt[1][1], nut[1][1]);
            swap(j1, j2);
        } else {
            if (j1 < j2) {
                minm = 0;
            }
        }
        if (j1 != 0) {
            update(1, 0, nn, 0, j1, li, nt[1][0], nut[1][0]);
            int y2 = get(1, 0, nn, 0, j1, nt[1][0], nut[1][0]);
            minm = min(minm, y2);
            update(1, 0, nn, 0, j1, -li, nt[1][0], nut[1][0]);
        }
        if (j2 != n) {
            update(1, 0, nn, j2, nn, -ri, nt[0][1], nut[0][1]);
            int y3 = get(1, 0, nn, j2, nn, nt[0][1], nut[0][1]);
            minm = min(minm, y3);
            update(1, 0, nn, j2, nn, ri, nt[0][1], nut[0][1]);
        }
        if (minm <= x) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
    return 0;
}
