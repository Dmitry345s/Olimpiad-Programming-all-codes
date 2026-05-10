#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long MAX  = 1e18 + 179;

struct for_g{
    int a, b, c;
};
int main() {
    int n;
    cin >> n;
    vector<for_g> g;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            if (x == 1e5) {
                continue;
            }
            g.push_back({i, j, x});
        }
    }

    vector<long long> d(n, MAX);
    vector<int> p(n, -1);
    int x;
    for (int k = 0; k < n + 1; ++k) {
        x = -1;
        for (int i = 0; i < g.size(); ++i) {
            if (d[g[i].b] > d[g[i].a] + g[i].c) {
                d[g[i].b] = d[g[i].a] + g[i].c;
                p[g[i].b] = g[i].a;
                x = g[i].b;
            }
        }
    }
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < n; ++i) {
            x = p[x];
        }
        vector<int> ans;
        int y = x;
        while (y != x || ans.size() < 1) {
            ans.push_back(y);
            y = p[y];
        }
        reverse(ans.begin(), ans.end());
        cout << ans.size() + 1 << endl;
        cout << x + 1 << " ";
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] + 1 << " ";
        }
    }
}
