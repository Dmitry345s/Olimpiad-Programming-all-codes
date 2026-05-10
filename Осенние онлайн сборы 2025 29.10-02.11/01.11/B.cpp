#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 4e6 + 1, LN = 31;
int p[MAX];

int root(int v) {
    if (p[v] == v) return v;
    return p[v] = root(p[v]);
}

int cnt;

void unite(int v, int u) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    p[u] = v;
    cnt--;
}

int solve(int x, int y) {
    if (y == -1) return 0;
    if (x == 0) return 1;
    int in = 0;
    for (int u = 0; u < LN; ++u) {
        if ((x >> u) & 1) {
            in = u;
        }
    }
    //cout << x << " " << y << endl;
    int cc = (y + 1) / (1ll << (in + 1));
    int cc2 = (y + 1) % (1ll << (in + 1));
    int ny = cc * (1ll << in) + min(cc2, (1ll << in));
    int cnt = max(cc - 1 + (cc2 != 0), 0ll);
    int nx = x - (1ll << in);
    //cout << nx << " " << ny << endl;
    if (nx != 0) {
        cnt = 0;
    }
    //cout << cnt << endl;
    return cnt + solve(nx, ny - 1);
}

int solve2(int x, int y, int y2) {
    return solve(x, y2) - solve(x, y) + ((x & y) == 0);
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    cnt = n * m;
    map<int, int> mp;
    for (int i = 0; i < LN; ++i) {
        mp[(1ll << i)] = i;
    }
    for (int i = 0; i < MAX; ++i) {
        p[i] = i;
    }
    vector<pair<int, int>> go = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << solve2(x1, y1, y2) + solve2(y1, x1, x2) - ((x1 & y1) == 0) << endl;
    }
}
