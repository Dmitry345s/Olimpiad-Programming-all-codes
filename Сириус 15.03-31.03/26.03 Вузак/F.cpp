#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, q;
    cin >> n;
    vector<pair<int, int>> ps(n);
    vector<int> bs;
    vector<array<int, 5>> all;
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].first >> ps[i].second;
        bs.push_back(ps[i].first);
        all.push_back({ps[i].second, ps[i].first, 0, 0});
    }
    cin >> q;
    int r = 0;
    for (int i = 0; i < q; ++i) {
        string ch;
        cin >> ch;
        if (ch == "r90") {
            int x, y;
            cin >> x >> y;
            for (int j = 0; j < n; ++j) {
                ps[j].first -= x;
                ps[j].second -= y;
                swap(ps[j].first, ps[j].second);
                ps[j].first = -ps[j].first;
                ps[j].first += x;
                ps[j].second += y;
            }
        } else if (ch == "r180") {
            int x, y;
            cin >> x >> y;
            for (int j = 0; j < n; ++j) {
                for (int l = 0; l < 2; ++l) {
                    ps[j].first -= x;
                    ps[j].second -= y;
                    swap(ps[j].first, ps[j].second);
                    ps[j].first = -ps[j].first;
                    ps[j].first += x;
                    ps[j].second += y;
                }
            }
        } else if (ch == "r270") {
            int x, y;
            cin >> x >> y;
            for (int j = 0; j < n; ++j) {
                for (int l = 0; l < 3; ++l) {
                    ps[j].first -= x;
                    ps[j].second -= y;
                    swap(ps[j].first, ps[j].second);
                    ps[j].first = -ps[j].first;
                    ps[j].first += x;
                    ps[j].second += y;
                }
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int ans = 0;
            for (int j = 0; j < n; ++j) {
                if (x1 <= ps[j].first && ps[j].first <= x2 && y1 <= ps[j].second && ps[j].second <= y2) {
                    ans++;
                }
            }
            cout << ans << endl;
        }
    }
}
