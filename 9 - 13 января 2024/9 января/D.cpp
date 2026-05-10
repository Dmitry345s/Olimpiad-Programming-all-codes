#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e5, MAX2 = 1e6;
vector<int> a(MAX), c(MAX);
vector<vector<int>> tree(4 * MAX);

vector<int> mmerge(vector<int> u, vector<int> b) {
    for (int i = 0; i < u.size(); ++i) {
        b.push_back(u[i]);
    }
    sort(b.begin(), b.end());
    return b;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {c[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
    //cout << v << endl;
}

int get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || ql >= r) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        int u = upper_bound(tree[v].begin(), tree[v].end(), qr) - tree[v].begin();
        //cout << v << " " << u << endl;
        return u;
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n, q, k, w;
    cin >> n >> q >> k >> w;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, vector<int>> mp;
    for (int i = n - 1; i >= 0; --i) {
        mp[a[i]].push_back(i);
        if (mp.find(a[i]) == mp.end() || mp.size() < k) {
            c[i] = 1e9;
        } else {
            c[i] = mp[a[i]][mp[a[i]].size() - k];
        }
    }
    //cout << 0 << endl;
    if (n <= 1e4 && q <= 1e4) {
        int s = 0;
        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if (t == 1) {
                int x, v;
                cin >> x >> v;
                x = (x - 1 + w * s) % n;
                v = (v - 1 + w * s) % MAX2 + 1;
                a[x] = v;
            } else {
                int l, r;
                cin >> l >> r;
                l = (l - 1 + w * s) % n;
                r = (r - 1 + w * s) % n;
                if (l > r) {
                    swap(l, r);
                }
                r++;
                //cout << l << " " << r << endl;
                unordered_map<int, int> st;
                int cnt = 0;
                for (int j = l; j < r; ++j) {
                    st[a[j]] += 1;
                    if (st[a[j]] == k) {
                        cnt += 1;
                    }
                }
                cout << cnt << endl;
                s = cnt;
            }
        }
    } else {
        build(1, 0, n);
        int s = 0;
        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            int l, r;
            cin >> l >> r;
            l = (l - 1 + w * s) % n;
            r = (r - 1 + w * s) % n;
            if (l > r) {
                swap(l, r);
            }
            r++;
            //cout << l << " " << r << endl;
            //cout << l << " " << r << endl;
            int cnt = get(1, 0, n, l, r);
            cout << cnt << endl;
            s = cnt;
        }
    }
    return 0;
}
