#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

using namespace std;

int k = 900;
vector<vector<int>> b, b2;
vector<int> ps1, ps2, ps3;
int n;

void push(int v) {
    if (ps1[v]) {
        reverse(b[v].begin(), b[v].end());
    }
    ps1[v] = 0;
}

void push2(int v) {
    if (ps2[v] != -1) {
        for (int i = 0; i < (int)b[v].size(); ++i) {
            b[v][i] = ps2[v];
        }
    }
    b2[v] = b[v];
    ps3[v] = 0;
    ps2[v] = -1;
}

void rebuild() {
    vector<int> a(n);
    int nl = 0;
    for (int i = 0; i < (int)b.size(); ++i) {
        push(i);
        for (int u = 0; u < (int)b[i].size(); ++u) {
            int j = nl + u;
            int x = b[i][u];
            if (ps2[i] != -1) {
                a[j] = ps2[i];
            } else {
                a[j] = x;
            }
        }
        nl += (int)b[i].size();
    }
    b.assign((n + k - 1) / k, {});
    ps1.assign((n + k - 1) / k, 0);
    ps2.assign((n + k - 1) / k, -1);
    ps3.assign((n + k - 1) / k, -1);
    for (int i = 0; i < n; ++i) {
        b[i / k].push_back(a[i]);
    }
    b2 = b;
}

void split(int x, int v, int nl) {
    push(v);
    vector<int> tr, tr2;
    for (int i = 0; i < (int)b[v].size(); ++i) {
        if (i + nl < x) {
            tr.push_back(b[v][i]);
        } else {
            tr2.push_back(b[v][i]);
        }
    }
    swap(b[v], tr);
    b2[v] = b[v];
    ps3[v] = -1;
    auto it = b.begin() + v + 1, it5 = b2.begin() + v + 1;
    auto it2 = ps1.begin() + v + 1, it3 = ps2.begin() + v + 1, it4 = ps3.begin() + v + 1;
    b.insert(it, tr2);
    ps1.insert(it2, ps1[v]);
    ps2.insert(it3, ps2[v]);
    ps3.insert(it4, ps3[v]);
    b2.insert(it5, tr2);
}

void mset(int l, int r, int x) {
    int nl = 0;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (nl >= r) return;
        if (nl < l && l < nl + (int)b[i].size() && nl < r && r < nl + (int)b[i].size()) {
            push(i);
            push2(i);
            for (int j = l - nl; j < r - nl; ++j) {
                b[i][j] = x;
            }
            b2[i] = b[i];
            ps3[i] = -1;
            return;
        }
        if (nl < l && l < nl + (int)b[i].size()) {
            push(i);
            push2(i);
            for (int j = l - nl; j < (int)b[i].size(); ++j) {
                b[i][j] = x;
            }
            b2[i] = b[i];
            ps3[i] = -1;
        }
        if (nl < r && r < nl + (int)b[i].size()) {
            push(i);
            push2(i);
            for (int j = 0; j < r - nl; ++j) {
                b[i][j] = x;
            }
            b2[i] = b[i];
            ps3[i] = -1;
        }
        if (l <= nl && nl + (int)b[i].size() <= r) {
            ps2[i] = x;
        }
        nl += (int)b[i].size();
    }
}

void revers(int l, int r) {
    int nl = 0;
    vector<int> tr;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (nl >= r) break;
        if (nl < l && l < nl + (int)b[i].size()) {
            split(l, i, nl);
        }
        if (nl < r && r < nl + (int)b[i].size()) {
            split(r, i, nl);
        }
        if (l <= nl && nl + (int)b[i].size() <= r) {
            tr.push_back(i);
            ps1[i] ^= 1;
        }
        nl += (int)b[i].size();
    }
    for (int i = 0; i < (int)tr.size() / 2; ++i) {
        int i2 = tr[i], j = tr[(int)tr.size() - i - 1];
        swap(b[i2], b[j]);
        swap(b2[i2], b2[j]);
        swap(ps1[i2], ps1[j]);
        swap(ps2[i2], ps2[j]);
        swap(ps3[i2], ps3[j]);
    }
}

int get(int l, int r, int x) {
    int ans = 0;
    int nl = 0;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (nl >= r) break;
        if (nl < l && r < nl + (int)b[i].size()) {
            push(i);
            for (int j = l - nl; j < r - nl; ++j) {
                if (ps2[i] != -1) {
                    if (ps2[i] >= x) {
                        ans++;
                    }
                } else {
                    if (b[i][j] >= x) {
                        ans++;
                    }
                }
            }
            return ans;
        }
        if (nl < l && l < nl + (int)b[i].size()) {
            push(i);
            for (int j = l - nl; j < (int)b[i].size(); ++j) {
                if (ps2[i] != -1) {
                    if (ps2[i] >= x) {
                        ans++;
                    }
                } else {
                    if (b[i][j] >= x) {
                        ans++;
                    }
                }
            }
        }
        if (nl < r && r < nl + (int)b[i].size()) {
            push(i);
            for (int j = 0; j < r - nl; ++j) {
                if (ps2[i] != -1) {
                    if (ps2[i] >= x) {
                        ans++;
                    }
                } else {
                    if (b[i][j] >= x) {
                        ans++;
                    }
                }
            }
        }
        if (l <= nl && nl + (int)b[i].size() <= r) {
            if (ps2[i] != -1) {
                if (ps2[i] >= x) {
                    ans += (int)b[i].size();
                }
            } else {
                if (ps3[i] == -1) {
                    sort(b2[i].begin(), b2[i].end());
                    ps3[i] = 0;
                }
                ans += (int)b2[i].size() - (lower_bound(b2[i].begin(), b2[i].end(), x) - b2[i].begin());
            }
        }
        nl += (int)b[i].size();
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    vector<int> a(n);
    b.assign((n + k - 1) / k, {});
    ps1.assign((n + k - 1) / k, 0);
    ps2.assign((n + k - 1) / k, -1);
    ps3.assign((n + k - 1) / k, -1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i / k].push_back(a[i]);
    }
    b2 = b;
    int q;
    cin >> q;
    string t;
    int l, r, x;
    for (int i = 0; i < q; ++i) {
        if (i % 1500 == 0) {
            rebuild();
        }
        cin >> t;
        cin >> l >> r;
        --l;
        if (t[0] == 'g') {
            cin >> x;
            cout << get(l, r, x) << '\n';
        } else if (t[0] == 's') {
            cin >> x;
            mset(l, r, x);
        } else {
            revers(l, r);
        }
    }
    return 0;
}
