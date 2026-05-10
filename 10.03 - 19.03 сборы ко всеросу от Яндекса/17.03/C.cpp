#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(179);
const int MAX = 5e5;
int cnt[2 * MAX + 1];

signed main() {
    int n, q;
    cin >> n >> q;
    vector<deque<int>> all(n + q);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a;
            cin >> a;
            all[i].push_back(a);
        }
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, y;
            cin >> i >> y;
            --i;
            all[i].push_back(y);
        } else if (t == 2) {
            int i;
            cin >> i;
            --i;
            all[i].pop_back();
        } else if (t == 4) {
            int a, b, c;
            cin >> a >> b >> c;
            --a; --b; --c;
            if ((int)all[a].size() < (int)all[b].size()) {
                while (!all[a].empty()) {
                    all[b].push_front(all[a].back());
                    all[a].pop_back();
                }
                swap(all[c], all[b]);
            } else {
                while (!all[b].empty()) {
                    all[a].push_back(all[b].front());
                    all[b].pop_front();
                }
                swap(all[c], all[a]);
            }
        } else {
            int m;
            cin >> m;
            vector<int> p(m);
            for (int i = 0; i < m; ++i) {
                cin >> p[i];
                --p[i];
            }
            for (int j = 0; j < (int)all[p.back()].size(); ++j) {
                cout << all[p.back()][j] << " ";
            }
            int ans = -1;
            vector<int> now;
            for (int j = 0; j < (int)now.size(); ++j) {
                cnt[now[j]]--;
            }
        }
    }
    return 0;
}
