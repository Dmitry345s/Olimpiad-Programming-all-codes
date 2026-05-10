#include<bits/stdc++.h>

using namespace std;

int k = 350;
vector<vector<int>> b;
vector<int> ans, ps, ls;

void push(int v) {
    if (ps[v]) {
        reverse(b[v].begin(), b[v].end());
    }
    ps[v] = 0;
}

void rebuild(int n) {
    vector<int> a(n);
    for (int i = 0; i < (int)b.size(); ++i) {
        push(i);
        for (int j = 0; j < (int)b[i].size(); ++j) {
            a[ls[i] + j] = b[i][j];
        }
    }
    b.assign((n + k - 1) / k, {});
    ans.assign((n + k - 1) / k, 2e9);
    ps.assign((n + k - 1) / k, 0);
    ls.assign((n + k - 1) / k, 2 * n);
    for (int i = 0; i < n; ++i) {
       b[i / k].push_back(a[i]);
       ans[i / k] = min(ans[i / k], a[i]);
       ls[i / k] = min(i, ls[i / k]);
    }
}

void split(int x) {
    int u = -1;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (ls[i] < x && x < ls[i] + (int)b[i].size()) {
            push(i);
            u = i;
            break;
        }
    }
    if (u == -1) return;
    vector<int> tr, tr2;
    int rans1 = 2e9, rans2 = 2e9;
    for (int i = 0; i < (int)b[u].size(); ++i) {
        if (ls[u] + i < x) {
            tr.push_back(b[u][i]);
            rans1 = min(rans1, b[u][i]);
        } else {
            tr2.push_back(b[u][i]);
            rans2 = min(rans2, b[u][i]);
        }
    }
    b.push_back(tr);
    b.push_back(tr2);
    ls.push_back(ls[u]);
    ls.push_back(ls[u] + (int)tr.size());
    ps.push_back(0);
    ps.push_back(0);
    ans.push_back(rans1);
    ans.push_back(rans2);
    auto it = b.begin() + u;
    auto it2 = ls.begin() + u, it3 = ps.begin() + u, it4 = ans.begin() + u;
    b.erase(it);
    ls.erase(it2);
    ps.erase(it3);
    ans.erase(it4);
}

void revers(int l, int r) {
    int m = (l + r) / 2;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (l <= ls[i] && ls[i] < r) {
            ls[i] = m + m - (ls[i] + (int)b[i].size() - 1);
            if ((l + r) % 2 == 0) {
                ls[i] -= 1;
            }
            ps[i] ^= 1;
        }
    }
}

int get(int l, int r) {
    int rans = 2e9;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (l <= ls[i] && ls[i] < r) {
            rans = min(ans[i], rans);
        }
    }
    return rans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    b.resize((n + k - 1) / k);
    ans.assign((n + k - 1) / k, 2e9);
    ps.assign((n + k - 1) / k, 0);
    ls.assign((n + k - 1) / k, 2 * n);
    for (int i = 0; i < n; ++i) {
       cin >> a[i];
       b[i / k].push_back(a[i]);
       ans[i / k] = min(ans[i / k], a[i]);
       ls[i / k] = min(i, ls[i / k]);
    }
    //cout << ans[0] << endl;
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        cnt++;
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        split(l); split(r);
        /*for (int i = 0; i < (int)b.size(); ++i) {
            cout << "! " << ls[i] << " " << ans[i] << " " << ps[i] << endl;
            for (int j = 0; j < (int)b[i].size(); ++j) {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }*/
        if (t == 1) {
            revers(l, r);
        } else {
            cout << get(l, r) << endl;
        }
        if (cnt == (k + 1) / 2) {
            rebuild(n);
            cnt = 0;
        }
    }
    return 0;
}
