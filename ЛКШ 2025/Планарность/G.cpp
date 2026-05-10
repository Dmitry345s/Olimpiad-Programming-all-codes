#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
vector<int> g[MAX];
int used[MAX];

mt19937 rnd(179);

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    for (int st = 0; st < 100 * n; ++st) {
        fill(used, used + n, -1);
        used[st % n] = 0;
        vector<int> nowans;
        nowans.push_back(st % n);
        for (int _ = 0; _ < 5000; ++_) {
            int nx = g[nowans.back()][rnd() % (int)g[nowans.back()].size()];
            if (used[nx] == -1) {
                used[nx] = (int)nowans.size();
                nowans.push_back(nx);
            } else {
                vector<int> nowst;
                while ((int)nowans.size() > used[nx] + 1) {
                    nowst.push_back(nowans.back());
                    nowans.pop_back();
                }
                for (auto v : nowst) {
                    used[v] = (int)nowans.size();
                    nowans.push_back(v);
                }
            }
            if ((int)nowans.size() == n) {
                for (int v : nowans) {
                    cout << v + 1 << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }
    //assert(false);
    return 0;
}
