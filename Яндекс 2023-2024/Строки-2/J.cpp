#include<bits/stdc++.h>

using namespace std;

int MAX = 505;
vector<vector<long long>> h(MAX, vector<long long> (MAX));
vector<long long> qs(MAX), ps(MAX);
int p = 256283, q = 724203;
long long mod = 1e9 + 11;

void build(vector<string> & s, int n, int m) {
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            int c = (int)s[i - 1][j - 1] - 97 + 1;
            h[i][j] = ((h[i - 1][j] * q) + (h[i][j - 1] * p) - ((h[i - 1][j - 1] * p) * q) + c);
        }
    }
    qs[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        qs[i] = (qs[i - 1] * q);
    }
    ps[0] = 1;
    for (int j = 1; j < m + 1; ++j) {
        ps[j] = (ps[j - 1] * p);
    }
}

long long get_hash(int l1, int r1, int l2, int r2) {
    long long hash1 = (h[l2][r2] + ((h[l1][r1] * qs[l2 - l1]) * ps[r2 - r1]));
    hash1 = (hash1 - (h[l1][r2] * qs[l2 - l1]));
    hash1 = (hash1 - (h[l2][r1] * ps[r2 - r1]));
    return hash1;
}

pair<int, int> ans1, ans2;

bool check(int x, int n, int m) {
    unordered_map<long long, pair<int, int>> mp;
    for (int i = 0; i < n - x + 1; ++i) {
        for (int j = 0; j < m - x + 1; ++j) {
            long long hash1 = get_hash(i, j, i + x, j + x);
            if (mp.find(hash1) != mp.end()) {
                ans1 = mp[hash1];
                ans2 = {i, j};
                return 1;
            }
            mp[hash1] = {i, j};
        }
    }
    return 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    char u = getchar();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = getchar();
            s[i].push_back(c);
        }
        u = getchar();
    }
    build(s, n, m);
    int l = 0, r = min(n, m) + 1;
    while (l + 1 < r) {
        int cen = (l + r) / 2;
        if (check(cen, n, m)) {
            l = cen;
        } else {
            r = cen;
        }
    }
    if (l == 0) {
        cout << 0 << endl;
        return 0;
    }
    check(l, n, m);
    cout << l << u;
    cout << ans1.first + 1 << " " << ans1.second + 1 << u;
    cout << ans2.first + 1 << " " << ans2.second + 1 << u;
    return 0;
}
