#include<iostream>
#include<vector>

using namespace std;

struct edge {
    int v, to, c;
    long long w;
};

vector<edge> g;

bool check(long long m, int n) {
    vector<long long> d(n, 3000);
    d[0] = 0;
    long long mw = 3000000 + m * 100;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g.size(); ++j) {
            if (g[j].w < mw) {
                continue;
            }
            if (d[g[j].to] > d[g[j].v] + g[j].c) {
                d[g[j].to] = d[g[j].v] + g[j].c;
            }
        }
    }
    if (d[n - 1] <= 1440) {
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, p;
    cin >> n >> p;
    int maxm = -1e9;
    for (int l = 0; l < p; ++l) {
        int v, to, c, w;
        cin >> v >> to >> c >> w;
        --v; --to;
        g.push_back({v, to, c, w});
        g.push_back({to, v, c, w});
        maxm = max(maxm, w);
    }
    int l = 0, r = maxm / 100 + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (check(m, n)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l;
    return 0;
}
