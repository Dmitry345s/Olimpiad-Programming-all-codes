#include<bits/stdc++.h>

using namespace std;

const int MAX = 102;

vector<int> g[MAX];
int pr[MAX], used[MAX];

bool try_kuhn(int v) {
    if (used[v]) return 0;
    used[v] = 1;
    for (int to : g[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to])) {
            pr[to] = v;
            return 1;
        }
    }
    return 0;
}

signed main() {
    int n, v;
    cin >> n >> v;
    vector<array<int, 3>> all(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int t = (s[0] - '0') * 60 * 10 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
        int x, y;
        cin >> x >> y;
        all[i] = {t, x, y};
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int dt = all[j][0] - all[i][0];
            int dx = abs(all[j][1] - all[i][1]);
            int dy = abs(all[j][2] - all[i][2]);
            long double dist = sqrtl(dx * dx + dy * dy);
            long double needt = (dist / ((long double)v / 60));
            if (needt <= dt) {
                g[i].push_back(j);
            }
        }
    }
    int ans = 0;
    fill(pr, pr + n, -1);
    for (int i = 0; i < n; ++i) {
        fill(used, used + n, 0);
        ans += try_kuhn(i);
    }
    cout << n - ans << endl;
    return 0;
}
