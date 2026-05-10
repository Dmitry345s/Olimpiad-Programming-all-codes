#include<iostream>
#include<vector>

using namespace std;

long long MAX = 1e18 + 179;

struct for_g{
    int a, b, c;
};

int main() {
    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f;
    vector<for_g> g;
    for (int l = 0; l < m; ++l) {
        int i, j, x;
        cin >> i >> j >> x;
        g.push_back({i - 1, j - 1, x});
    }
    vector<long long> d(n, MAX);
    d[s - 1] = 0;
    for (int i = 0; i < k; ++i) {
        vector<long long> new_d(n);
        for (int l = 0; l < n; ++l) {
            new_d[l] = d[l];
        }
        for (int j = 0; j < m; ++j) {
            if (d[g[j].b] > d[g[j].a] + g[j].c) {
                new_d[g[j].b] = d[g[j].a] + g[j].c;
            }
        }
        for (int l = 0; l < n; ++l) {
            d[l] = new_d[l];
        }
    }
    if (d[f - 1] == MAX) {
        cout << -1 << endl;
    } else {
        cout << d[f - 1] << endl;
    }
    return 0;
}
