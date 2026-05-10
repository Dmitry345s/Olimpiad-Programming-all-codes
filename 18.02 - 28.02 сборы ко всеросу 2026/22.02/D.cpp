#include<bits/stdc++.h>

using namespace std;

const int MAX = 3005;
const int C = 2 * MAX;

vector<pair<int, int>> gor[C + 2 * MAX];
vector<pair<int, int>> gol[C + 2 * MAX];
long long ans[2][C];
vector<pair<int, int>> qs[C + 2 * MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        int a, b, t, c;
        cin >> t >> a >> b >> c;
        a *= 2;
        b *= 2;
        t *= 2;
        c /= 2;
        int nt = t;
        if (a < b) {
            for (int l = a; l < b; ++l) {
                gor[nt].push_back({l, c});
                nt++;
            }
        } else if (a > b) {
            for (int l = a; l > b; --l) {
                gol[nt].push_back({l, c});
                nt++;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        int t, x;
        cin >> t >> x;
        t *= 2;
        x *= 2;
        qs[t].push_back({x, i});
    }
    vector<long long> rans(q);
    for (int i = C - 1; i >= 0; --i) {
        ans[0][i] = 0;
    }
    //if (q > 100) exit(0);
    for (int i = C - 2 + 2 * MAX; i >= 0; --i) {
        //if (q > 100 && i < C) break;
        int y = i % 2;
        for (auto [j, c] : gor[i]) {
            //cout << j << " " << c << endl;
            if (j + 1 < C) ans[1 ^ y][j] = max(ans[1 ^ y][j], ans[0 ^ y][j + 1] + c);
        }
        for (auto [j, c] : gol[i]) {
            //cout << j << " " << c << endl;
            if (j - 1 >= 0) ans[1 ^ y][j] = max(ans[1 ^ y][j], ans[0 ^ y][j - 1] + c);
        }
        for (int j = 0; j < C; ++j) {
            ans[1 ^ y][j] = max(ans[1 ^ y][j], ans[0 ^ y][j]);
            if (j > 0) ans[1 ^ y][j] = max(ans[1 ^ y][j], ans[0 ^ y][j - 1]);
            if (j < C - 1) ans[1 ^ y][j] = max(ans[1 ^ y][j], ans[0 ^ y][j + 1]);
        }
        for (auto [x, in] : qs[i]) {
            rans[in] = ans[1 ^ y][x];
        }
    }
    //if (q > 100) exit(0);
    for (int i = 0; i < q; ++i) {
        cout << rans[i] << '\n';
    }
    return 0;
}
