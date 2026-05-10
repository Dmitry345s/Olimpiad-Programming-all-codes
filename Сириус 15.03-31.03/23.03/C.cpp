#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 3e5;
vector<int> pref(MAX);
int n;

bool in(int p, int l, int r) {
    if (l <= r) {
        return l <= p && p <= r;
    } else {
        return l <= p && p <= n - 1 || 0 <= p && p <= r;
    }
}

int get(int l, int r) {
    if (l <= r) {
        return pref[r] - pref[l];
    } else {
        return pref[n] - pref[l] + pref[r];
    }
}

signed main() {
    int q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    vector<array<int, 2>> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i][0] >> qs[i][1];
    }
    int ans = 1e15;
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<vector<pair<int, int>>> g(n);
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                g[(i + 1) % n].push_back({i, a[i]});
            } else {
                g[i].push_back({(i + 1) % n, a[i]});
            }
        }
        vector<vector<int>> dist(n, vector<int> (n));
        for (int i = 0; i < n; ++i) {
            vector<int> d(n, 1e15);
            set<pair<int, int>> mq;
            d[i] = 0;
            mq.insert({0, i});
            while (!mq.empty()) {
                int v = mq.begin()->second;
                mq.erase(mq.begin());
                for (auto [to, c] : g[v]) {
                    if (d[to] > d[v] + c) {
                        mq.erase({d[to], to});
                        d[to] = d[v] + c;
                        mq.insert({d[to], to});
                    }
                }
            }
            dist[i] = d;
        }
        int sum = 0;
        for (int i = 0; i < q; ++i) {
            sum += dist[qs[i][0]][qs[i][1]];
        }
        ans = min(ans, sum);
    }
    if (ans == 1e15) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
