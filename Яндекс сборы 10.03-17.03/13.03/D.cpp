#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> ans;
mt19937 rnd(228);
int cnt = 0;

int ch(int n, int a, int b) {
    cnt++;
    assert(cnt <= 45000);
    cout << "? " << a << " " << b << " ";
    for (int i = 0; i < n; ++i) {
        if (i != a && i != b) {
            cout << 0 << " ";
        } else {
            cout << 1 << " ";
        }
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}

int in_one(int n, int a, int b, int c) {
    cnt++;
    assert(cnt <= 45000);
    cout << "? " << a << " " << b << " ";
    for (int i = 0; i < n; ++i) {
        if (i == c) {
            cout << 0 << " ";
        } else {
            cout << 1 << " ";
        }
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}

void solve(vector<int> now, int n) {
    if ((int)now.size() == 1) return;
    int c = now[rnd() % (int)now.size()];
    vector<vector<int>> all;
    for (int v : now) {
        if (v == c) continue;
        int fl = -1;
        for (int i = 0; i < (int)all.size(); ++i) {
            if (in_one(n, all[i][0], v, c)) {
                fl = i;
                break;
            }
        }
        if (fl != -1) {
            all[fl].push_back(v);
        } else {
            all.push_back({v});
        }
    }
    for (auto val : all) {
        for (int i = 0; i < (int)val.size(); ++i) {
            int v = val[i];
            if (ch(n, c, v)) {
                ans.push_back({c, v});
                swap(val[i], val[0]);
                solve(val, n);
                break;
            }
        }
    }
}

signed main() {
    int t, n;
    cin >> t >> n;
    vector<int> now;
    for (int i = 0; i < n; ++i) now.push_back(i);
    solve(now, n);
    cout << "! " << (int)ans.size() <<  endl;
    for (auto [u, v] : ans) {
        if (u > v) swap(u, v);
        cout << u << " " << v << endl;
    }
    return 0;
}
