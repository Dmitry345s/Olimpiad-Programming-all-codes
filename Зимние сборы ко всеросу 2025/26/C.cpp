#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e15;

signed main() {
    int a, b, m;
    cin >> a >> b >> m;
    vector<array<int, 3>> my(a), nm(b);
    for (int i = 0; i < a; ++i) {
        cin >> my[i][0] >> my[i][1] >> my[i][2];
    }
    for (int i = 0; i < b; ++i) {
        cin >> nm[i][0] >> nm[i][1] >> nm[i][2];
    }
    vector<pair<int, int>> mm(m);
    for (int i = 0; i < m; ++i) {
        cin >> mm[i].first >> mm[i].second;
    }
    sort(mm.begin(), mm.end());
    mm.insert(mm.begin(), {(int)-4e6, 0});
    mm.push_back({(int)4e6, 0});
    vector<pair<vector<int>, vector<int>>> prec((int)mm.size());
    for (int i = 0; i < (int)mm.size(); ++i) {
        prec[i].first.assign(mm[i].second + 2, 0);
        prec[i].second.assign(mm[i].second + 2, 0);
        for (int u = 0; u < a; ++u) {
            if (my[u][0] <= mm[i].first) {
                int dist = mm[i].first - my[u][0];
                int h = min(my[u][2], max(0ll, mm[i].second - (mm[i].first - my[u][0])));
                prec[i].first[min(mm[i].second + 1, dist)] += h * my[u][1];
            } else {
                int dist = my[u][0] - mm[i].first;
                int h = min(my[u][2], max(0ll, mm[i].second - (my[u][0] - mm[i].first)));
                prec[i].second[min(mm[i].second + 1, dist)] += h * my[u][1];
            }
        }
        for (int u = 0; u < b; ++u) {
            if (nm[u][0] <= mm[i].first) {
                int dist = mm[i].first - nm[u][0];
                int h = min(nm[u][2], max(0ll, mm[i].second - (mm[i].first - nm[u][0])));
                prec[i].first[min(mm[i].second + 1, dist)] += -h * nm[u][1];
            } else {
                int dist = nm[u][0] - mm[i].first;
                int h = min(nm[u][2], max(0ll, mm[i].second - (nm[u][0] - mm[i].first)));
                prec[i].second[min(mm[i].second + 1, dist)] += -h * nm[u][1];
            }
        }
        int sum = 0;
        for (int j = 0; j < (int)prec[i].first.size(); ++j) {
            sum += prec[i].first[j];
            prec[i].first[j] = sum;
        }
        sum = 0;
        for (int j = 0; j < (int)prec[i].second.size(); ++j) {
            sum += prec[i].second[j];
            prec[i].second[j] = sum;
        }
    }
    //cout << prec[1].second.back() << endl;
    //cout << 0 << endl;
    vector<int> dp((int)mm.size(), -INF);
    dp[0] = 0;
    for (int i = 1; i < (int)mm.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (mm[i].first - mm[j].first <= abs(mm[i].second - mm[j].second)) {
                continue;
            }
            //cout << i << " " << j << " ";
            int del = 0;
            int t = (mm[j].second - mm[i].second + mm[j].first + mm[i].first) / 2;
            //cout << t << " ";
            int u1 = t - mm[j].first;
            del += prec[j].second[min((int)prec[j].second.size() - 1, u1)];
            //cout << del << " ";
            int u2 = mm[i].first - t - 1;
            del += prec[i].first[min((int)prec[i].first.size() - 1, u2)];
            //cout << del << endl;
            dp[i] = max(dp[i], dp[j] + del);
        }
        //cout << dp[i] << endl;
    }
    cout << max(0ll, dp.back()) << endl;
    return 0;
}
