#include<bits/stdc++.h>
#define int long long

using namespace std;

bool check(vector<int> a, int m, int v, int p, int x) {
    int ch = a[x] + m;
    int c = (v - x - 1) * m;
    if (c < 0) c = 0;
    int in = x + 1;
    for (int i = x + 1; i < a.size(); ++i) {
        int del = ch - a[i];
        if (del < 0) break;
        int c2 = c - del;
        if (c2 < 0) {
            c = 0;
            in = i + 1;
            continue;
        }
        int to = (a.size() - i - 1);
        if (!to) {
            if (c + a.back() <= ch) {
                in = i + 1;
            }
            break;
        }
        if ((c2 + to - 1) / to <= m) {
            c = c2;
            in = i + 1;
        } else {
            break;
        }
    }
    return in > a.size() - p;
}

signed main() {
    int n, m, v, p;
    cin >> n >> m >> v >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int l = -1, r = a.size() - 1;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        if (check(a, m, v, p, c)) {
            r = c;
        } else {
            l = c;
        }
    }
    cout << n - r << endl;
    return 0;
}
