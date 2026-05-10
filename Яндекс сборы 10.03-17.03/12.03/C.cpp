#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<string> f(n);
    for (int i = 0; i < n; ++i) cin >> f[i];
    vector<vector<int>> sum(n, vector<int> (n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum[i][j + 1] = sum[i][j] + j * (f[i][j] - '0');
        }
    }
    vector<vector<int>> cnt(n, vector<int> (n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt[i][j + 1] = cnt[i][j] + (f[i][j] - '0');
        }
    }
    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int a = (x2 - x1) / (y2 - y1);
        int ans1 = 0;
        int ans2 = 0;
        for (int st = x1; st < x2; st += a) {
            int y = y1 + (st - x1) / a;
            ans2 += cnt[y][x2] - cnt[y][st + a];
            int sum1 = sum[y][st + a] - sum[y][st];
            int cnt1 = cnt[y][st + a] - cnt[y][st];
            ans1 += 2 * (sum1 - cnt1 * st) + cnt1;
        }
        //cout << ans1 << " " << ans2 << endl;
        cout << setprecision(30) << (double)ans1 / (2 * a) + ans2 << '\n';
    }
    return 0;
}
