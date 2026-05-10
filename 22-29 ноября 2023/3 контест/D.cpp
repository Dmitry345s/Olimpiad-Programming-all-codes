#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 5e3, MAX2 = 5e5;
vector<vector<pair<int, int>>> g(MAX2);
vector<int> c(MAX2);
vector<int> dp(MAX);
vector<int> h(MAX);

void dfs(int v, int p) {
    vector<int> ans;
    for (auto [to, i] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        ans.push_back(h[to] + c[i]);
    }
    if (ans.size() == 0) {
        h[v] = 0;
        dp[v] = 0;
        return;
    }
    sort(ans.begin(), ans.end());
    h[v] = ans.back();
    dp[v] = h[v];
    if (ans.size() > 1) {
        dp[v] += ans[(int)ans.size() - 2];
    }
}

vector<int> ps(MAX2), ps2(MAX2);
vector<pair<int, int>> dp2(MAX2);
vector<int> dp3(MAX2);

void dfs2(int v, int p) {
    ps[v] = p;
    int cnt = 0;
    for (auto [to, i] : g[v]) {
        if (to == p) continue;
        ps2[i] = to;
        dfs2(to, v);
        if (cnt == 0) {
            dp2[v].first = max(dp2[to].first, dp2[to].second) + c[i];
        } else {
            dp2[v].second = max(dp2[to].first, dp2[to].second) + c[i];
        }
        cnt++;
        dp3[v] = max(dp3[v], dp3[to]);
    }
    dp3[v] = max(dp3[v], dp2[v].first + dp2[v].second);
}

void up2(int v) {
    int cnt = 0;
    int rv = ps[v];
    dp3[rv] = 0;
    for (auto [to, i] : g[rv]) {
        if (to == ps[rv]) continue;
        if (to == v) {
            if (cnt == 0) {
                dp2[rv].first = max(dp2[to].first, dp2[to].second) + c[i];
            } else {
                dp2[rv].second = max(dp2[to].first, dp2[to].second) + c[i];
            }
        }
        cnt++;
        dp3[rv] = max(dp3[rv], dp3[to]);
    }
    dp3[rv] = max(dp3[rv], dp2[rv].first + dp2[rv].second);
}

void up(int v, int ch) {
    int cnt = 0;
    int rv = ps[v];
    dp3[rv] = 0;
    for (auto [to, i] : g[rv]) {
        if (to == ps[rv]) continue;
        if (to == v) {
            //cout << i << " " << c[i] << " " << cnt << endl;
            if (cnt == 0) {
                dp2[rv].first = dp2[rv].first - c[i] + ch;
            } else {
                dp2[rv].second = dp2[rv].second - c[i] + ch;
            }
            c[i] = ch;
        }
        dp3[rv] = max(dp3[rv], dp3[to]);
        cnt++;
    }
    dp3[rv] = max(dp3[rv], dp2[rv].first + dp2[rv].second);
    v = rv;
    while(v != 0) {
        //cout << v << " " << dp3[v] << " " << dp2[v].first << " " << dp2[v].second << endl;
        up2(v);
        v = ps[v];
    }
}

signed main() {
    int n, q, w;
    cin >> n >> q >> w;
    bool flag = 1;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b >> c[i];
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        if (a != 0) {
            flag = 0;
        }
    }
    int con = 5000;
    if (n <= con && q <= con) {
        int last = 0;
        for (int i = 0; i < q; ++i) {
            int d, e;
            cin >> d >> e;
            d = (d + last) % (n - 1);
            e = (e + last) % w;
            c[d] = e;
            dp.assign(MAX, 0);
            h.assign(MAX, 0);
            dfs(0, 0);
            last = 0;
            for (int i = 0; i < n; ++i) {
                last = max(last, dp[i]);
            }
            cout << last << '\n';
        }
    } else if (flag) {
        set<pair<int, int>> st;
        for (int i = 0; i < n - 1; ++i) {
            st.insert({-c[i], i});
        }
        int last = 0;
        for (int i = 0; i < q; ++i) {
            int d, e;
            cin >> d >> e;
            d = (d + last) % (n - 1);
            st.erase({-c[d], d});
            e = (e + last) % w;
            c[d] = e;
            st.insert({-c[d], d});
            if (n == 2) {
                auto it = st.begin();
                last = -(*it).first;
                cout << last << endl;
                continue;
            }
            auto it = st.begin(), it2 = (it++);
            last = -((*it).first + (*it2).first);
            cout << last << endl;
        }
    } else {
        int last = 0;
        dfs2(0, 0);
        //cout << dp3[0] << endl;
        for (int i = 0; i < q; ++i) {
            int d, e;
            cin >> d >> e;
            d = (d + last) % (n - 1);
            e = (e + last) % w;
            //cout << ps2[d] << " " << e << " " << ps[ps2[d]] << endl;
            up(ps2[d], e);
            last = dp3[0];
            cout << last << endl;
        }
    }
}
