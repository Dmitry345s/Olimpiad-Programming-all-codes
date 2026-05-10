#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<pair<int, int>> all;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            all.push_back({x, y});
        }
        int ax, ay;
        int bx, by;
        cin >> ax >> ay >> bx >> by;
        int a = by - ay;
        int b = ax - bx;
        int c = -(a * ax + b * ay);
        int na = -b;
        int nb = a;
        int stx = na * ax + nb * ay;
        int enx = na * bx + nb * by;
        int fl = 1;
        if (stx > enx) {
            fl = -1;
            swap(stx, enx);
        }
        vector<pair<int, int>> nx;
        vector<int> tr;
        tr.push_back(stx);
        tr.push_back(enx);
        map<int, vector<int>> go;
        for (int i = 0; i < n; ++i) {
            int x = na * all[i].first + nb * all[i].second;
            x *= fl;
            int d = abs(a * all[i].first + b * all[i].second + c);
            if (stx <= x && x + d <= enx) {
                tr.push_back(x);
                tr.push_back(x + d);
                //cout << i << " " << x << " " << x + d << endl;
                go[x + d].push_back(x);
            }
        }
        sort(tr.begin(), tr.end());
        tr.erase(unique(tr.begin(), tr.end()), tr.end());
        vector<int> dp((int)tr.size());
        dp[0] = 0;
        for (int i = 1; i < (int)tr.size(); ++i) {
            int nx = tr[i];
            dp[i] = dp[i - 1];
            int cnt = 0;
            for (int x : go[nx]) {
                int j = lower_bound(tr.begin(), tr.end(), x) - tr.begin();
                if (i == j) {
                    cnt++;
                    continue;
                }
                dp[i] = max(dp[i], dp[j] + 1);
            }
            dp[i] += cnt;
        }
        cout << dp.back() << endl;
    }
    return 0;
}
