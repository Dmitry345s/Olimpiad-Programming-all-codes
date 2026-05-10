#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 1;
vector<int> all[MAX];
int n;

bool ch(int d, string t) {
    int now = 0;
    for (int i = 0; i < (int)t.size(); ++i) {
        if (now >= n || all[now][t[i] - 'a'] == -1) return 0;
        now = all[now][t[i] - 'a'];
        now += d;
    }
    return 1;
}

int solve(string t) {
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (ch(m, t)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (l == 0) {
        return -1;
    }
    return l;
}

signed main() {
    int q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> now(26, -1);
    all[n] = now;
    for (int i = n - 1; i >= 0; --i) {
        now[s[i] - 'a'] = i;
        all[i] = now;
    }
    for (int i = 0; i < q; ++i) {
        string t;
        cin >> t;
        cout << solve(t) << endl;
    }
    return 0;
}
