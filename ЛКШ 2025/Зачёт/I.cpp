#include<bits/stdc++.h>

using namespace std;

const int C = 4;

map<array<int, C>, int> all;

int tr(array<int, C> a) {
    int sum = 0;
    for (int i = 0; i < C; ++i) {
        sum += a[i];
    }
    if (sum == 1) {
        all[a] = 0;
    }
    if (all.find(a) != all.end()) return all[a];
    vector<int> ch;
    for (int i = 0; i < C; ++i) {
        for (int j = 1; j <= a[i]; ++j) {
            if (j == a[i] && sum == a[i]) continue;
            a[i] -= j;
            ch.push_back(tr(a));
            a[i] += j;
        }
    }
    sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());
    int ans = 0;
    while (ans < (int)ch.size() && ch[ans] == ans) ans++;
    all[a] = ans;
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ans ^= a[i];
        mx = max(mx, a[i]);
    }
    if (mx == 1) {
        if (ans == 0) {
            cout << "FIRST" << endl;
        } else {
            cout << "SECOND" << endl;
        }
    } else {
        if (ans == 0) {
            cout << "SECOND" << endl;
        } else {
            cout << "FIRST" << endl;
        }
    }
    /*int u = tr({10, 10, 10, 10});
    int fl = 1;
    for (auto [key, val] : all) {
        int tt = 0;
        int mx = 0;
        for (int i = 0; i < C; ++i) {
            cout << key[i] << " ";
            mx = max(mx, key[i]);
            tt ^= key[i];
        }
        if (mx > 1 && (val == 0 && tt != 0 || tt == 0 && val != 0)) {
            fl = 0;
        }
        cout << " " << val << " " << tt << endl;
    }
    cout << fl << endl;*/
}
