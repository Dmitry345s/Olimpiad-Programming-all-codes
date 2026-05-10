#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 1;
int ans[MAX];
int n;

int get(int l, int r) {
    vector<char> now(n, '0');
    for (int i = l; i < r; ++i) {
        now[i] = '1';
    }
    cout << "Q ";
    for (int i = 0; i < n; ++i) {
        cout << now[i];
    }
    cout << endl;
    char nans;
    cin >> nans;
    if (nans == 'P') return 1;
    return 0;
}

void solve(int l, int r) {
    //if (cnt > C) return;
    if (l + 2 == r) {
        ans[l] = get(l, l + 1);
        ans[r] = get(r, r + 1);
    }
    int ch = get(l, r);
    if (ch == 0) return;
    if (l + 1 == r) {
        ans[l] = 1;
        return;
    }
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
}

int C;

int get2(int l, int r) {
    int rl = l * C, rr = min(r * C, n);
    return get(rl, rr);
}

void solve2(int l, int r) {
    int ch = get2(l, r);
    if (ch == 0) return;
    if (l + 1 == r) {
        solve(l * C, min(r * C, n));
        return;
    }
    int m = (l + r) / 2;
    solve2(l, m);
    solve2(m, r);
}

signed main() {
    int t;
    long double p;
    cin >> n >> p >> t;
    int u = p * 1000;
    if (p == 0) {
        C = 1000;
    } else {
        C = 8;
    }
    while (t--) {
        fill(ans, ans + n, 0);
        solve2(0, (n + C - 1) / C);
        cout << "A ";
        for (int i = 0; i < n; ++i) {
            cout << ans[i];
        }
        cout << endl;
        char y;
        cin >> y;
        if (y == 'W') return 0;
    }
}
