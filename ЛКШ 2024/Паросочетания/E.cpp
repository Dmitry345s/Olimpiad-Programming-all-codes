#include<bits/stdc++.h>

using namespace std;

const int MAX = 1000;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
vector<int> now_pair(MAX, -1);
int timer = 1;

bool try_kuhn(int v) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1 || try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}

signed main() {
    int m;
    cin >> m;
    vector<array<int, 6>> all;
    for (int i = 0; i < m; ++i) {
        string s;
        int a, b, c, d;
        cin >> s >> a >> b >> c >> d;
        int time = (s[0] - '0') * 10 * 60 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
        int time2 = time + abs(a - c) + abs(b - d);
        //cout << time << " " << time2 << endl;
        all.push_back({time, time2, a, b, c, d});
    }
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            //cout << i << " " << j << endl;
            if (all[i][1] + abs(all[i][4] - all[j][2]) + abs(all[i][5] - all[j][3]) < all[j][0]) {
                g[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        if (try_kuhn(i)) {
            timer++;
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (now_pair[i] == -1) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
