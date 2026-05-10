#include<bits/stdc++.h>

using namespace std;

int get(int x) {
    cout << "? " << x + 1 << endl;
    int ans;
    cin >> ans;
    return ans;
}

const int C = 500;
const int MAX = 20000;
int us[MAX];
vector<pair<int, int>> rans;
vector<int> to_ch;

void solve(int l, int r, vector<int> & now, int ch) {
    if (l + 1 == r) {
        us[to_ch[l]] = 1;
        us[now[0]] = 1;
        rans.push_back({to_ch[l], now[0]});
        return;
    }
    int m = (l + r) / 2;
    vector<int> to_l;
    vector<int> to_r;
    int cnt = -1;
    int chl = -1, chr = -1;
    if (ch) {
        for (int i = l; i < m; ++i) {
            cnt = get(to_ch[i]);
        }
        chl = 0;
        chr = 1;
    } else {
        for (int i = l; i < m; ++i) {
            cnt = get(to_ch[i]);
        }
        chl = 1;
        chr = 0;
    }
    for (int v : now) {
        if ((int)to_l.size() == m - l) {
            to_r.push_back(v);
            continue;
        }
        if ((int)to_r.size() == r - m) {
            to_l.push_back(v);
            continue;
        }
        int u = get(v);
        if (!ch) {
            if (u == cnt) {
                to_l.push_back(v);
            } else {
                to_r.push_back(v);
                cnt = u;
            }
        } else {
            if (u == cnt) {
                to_r.push_back(v);
            } else {
                to_l.push_back(v);
                cnt = u;
            }
        }
    }
    solve(l, m, to_l, chl);
    solve(m, r, to_r, chr);
}

mt19937 rnd(57);

signed main() {
    int n;
    cin >> n;
    vector<int> to_f;
    int ws = 0;
    vector<int> ord;
    for (int i = 0; i < 2 * n; ++i) {
        ord.push_back(i);
    }
    //shuffle(ord.begin(), ord.end(), rnd);
    for (int i : ord) {
        if ((int)to_ch.size() == n) {
            to_f.push_back(i);
            continue;
        }
        if ((int)to_f.size() == n) {
            to_ch.push_back(i);
            continue;
        }
        int ans = get(i);
        if (ans != ws) {
            to_ch.push_back(i);
            ws = ans;
        } else {
            to_f.push_back(i);
        }
    }
    solve(0, n, to_f, 1);
    cout << "! ";
    for (auto [u, v] : rans) {
        cout << u + 1 << " " << v + 1 << " ";
    }
    cout << endl;
    return 0;
}
