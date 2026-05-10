#include<bits/stdc++.h>

using namespace std;

int n;

int solve0(int l, int r) {
    if (l + 1 == r) {
        return 0;
    }
    int m = (l + r) / 2;
    int ch1 = solve0(l, m);
    int ch2 = solve0(m, r);
    int ch = max(ch1, ch2) + 1;
    if (!(l == 0 && r == n)) {
        cout << "a" << ch << "[" << l << "] = ";
        if (ch1 == 0) {
            cout << "in";
        } else {
            cout << "a" << ch1;
        }
        cout << "[" << l << "] + ";
        if (ch2 == 0) {
            cout << "in";
        } else {
            cout << "a" << ch2;
        }
        cout << "[" << m << "]" << endl;
    } else {
        cout << "out[0] = a" << ch1 << "[" << 0 << "] + " << "a" << ch2 << "[" << m << "]" << endl;
    }
    return ch;
}

void pr(int ch) {
    if (ch == 0) {
        cout << "out";
        return;
    }
    cout << "a" << ch;
}

void solve1(int l, int r, int ch) {
    if (l + 1 == r) {
        pr(ch);
        cout << "[" << l << "]" << " = " << "in[" << l << "] + 0" << endl;
        return;
    }
    int m = (l + r) / 2;
    solve1(l, m, ch);
    solve1(m, r, ch + 1);
    for (int i = m; i < r; ++i) {
        pr(ch);
        cout << "[" << i << "]" << " = ";
        pr(ch + 1);
        cout << "[" << i << "]" << " + ";
        pr(ch);
        cout << "[" << m - 1 << "]" << endl;
    }
}

void solve2(int l, int r, int ch) {
    if (l + 1 == r) {
        pr(ch);
        cout << "[" << l << "] = ";
        cout << "in[" << l << "] max 0" << endl;
        cout << "lf" << ch;
        cout << "[" << l << "] = ";
        cout << "in[" << l << "] max 0" << endl;
        cout << "rg" << ch;
        cout << "[" << l << "] = ";
        cout << "in[" << l << "] max 0" << endl;
        cout << "sum" << ch;
        cout << "[" << l << "] = ";
        cout << "in[" << l << "] + 0" << endl;
        return;
    }
    int m = (l + r) / 2;
    solve2(l, m, ch + 1);
    solve2(m, r, ch + 1);

    cout << "temp" << ch;
    cout << "[" << l << "] = ";
    pr(ch + 1);
    cout << "[" << l << "] max ";
    pr(ch + 1);
    cout << "[" << m << "]" << endl;

    cout << "sum" << ch;
    cout << "[" << l << "] = ";
    cout << "sum" << ch + 1 << "[" << m << "] + ";
    cout << "sum" << ch + 1 << "[" << l << "]" << endl;

    cout << "rtemp" << ch << "[" << l << "] = ";
    cout << "sum" << ch + 1 << "[" << l << "] + ";
    cout << "rg" << ch + 1 << "[" << m << "]" << endl;

    cout << "ltemp" << ch << "[" << l << "] = ";
    cout << "sum" << ch + 1 << "[" << m << "] + ";
    cout << "lf" << ch + 1 << "[" << l << "]" << endl;

    cout << "sumtemp" << ch << "[" << l << "] = ";
    cout << "rg" << ch + 1 << "[" << m << "] + ";
    cout << "lf" << ch + 1 << "[" << l << "]" << endl;

    pr(ch);
    cout << "[" << l << "] = ";
    cout << "sumtemp" << ch << "[" << l << "] max ";
    cout << "temp" << ch << "[" << l << "]" << endl;

    cout << "rg" << ch << "[" << l << "] = ";
    cout << "rg" << ch + 1 << "[" << l << "] max ";
    cout << "rtemp" << ch << "[" << l << "]" << endl;

    cout << "lf" << ch << "[" << l << "] = ";
    cout << "lf" << ch + 1 << "[" << m << "] max ";
    cout << "ltemp" << ch << "[" << l << "]" << endl;
}

signed main() {
    freopen("06.in.txt", "r", stdin);
    freopen("06.txt", "w", stdout);
    int t, _;
    cin >> t >> n >> _;
    if (t == 1) {
        int u = solve0(0, n);
    } else if (t == 2) {
        int c = 62;
        int cnt = 0;
        for (int i = 0; i < n; i += c) {
            //cnt++;
            solve1(i, min(i + c, n), i / c);
        }
        int ls = c - 1;
        for (int i = c; i < n; i += c) {
            for (int j = i; j < min(i + c, n); ++j) {
                pr(0);
                cout << "[" << j << "]" << " = ";
                pr(i / c);
                cout << "[" << j << "]" << " + ";
                pr(0);
                cout << "[" << ls << "]" << endl;
            }
            ls = i + c - 1;
        }
        //cout << cnt << endl;
    } else {
        solve2(0, n, 0);
        //cout << "out[0] = a0[0] max 0" << endl;
    }
}
