#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")

using namespace std;
using ll = int;

const int MAX = 6e3 + 5, ONE = 1, Z = 0;

int tree[2 * MAX];
int dp[2 * MAX];

void build() {
    for (int i = 1; i < 2 * MAX; ++i) {
        tree[i] = 0;
        dp[i] = 0;
    }
}

void update(int in, int x) {
    int v = in + MAX;
    tree[v] = x;
    while (v != 1) {
        v = (v >> 1);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }

}

int get(int ql, int qr) {
    int l = ql + MAX, r = qr + MAX;
    int ansl = 0, ansr = 0;
    while (l < r) {
        if ((l & 1)) {
            ansl = max(ansl, tree[l]);
        }
        l = ((l + 1) >> 1);
        if (!(r & 1)) {
            ansr = max(ansr, tree[r]);
        }
        r = ((r - 1) >> 1);
    }
    int ans = max(ansl, ansr);
    if (l == r) {
        ans = max(ans, tree[l]);
    }
    return ans;
}

signed main() {
    //cout << (2 >> 1) << endl;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> ch(n);
    vector<pair<ll, ll>> ch2(n);
    vector<ll> all;
    for (int i = 0; i < n; ++i) {
        cin >> ch2[i].first >> ch2[i].second;
        all.push_back(ch2[i].first);
        all.push_back(ch2[i].second);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for (int i = 0; i < n; ++i) {
        ch[i].first = lower_bound(all.begin(), all.end(), ch2[i].first) - all.begin() + 1;
        ch[i].second = lower_bound(all.begin(), all.end(), ch2[i].second) - all.begin() + 1;
    }
    vector<array<int, 3>> als;
    for (int i = 0; i < n; ++i) {
        als.push_back({ch[i].first, -1, i});
        als.push_back({ch[i].second, 1, i});
    }
    sort(als.begin(), als.end());
    vector<int> now(n, Z);
    vector<int> ans(n, ONE);
    vector<int> ans1(n, Z);
    set<array<int, 3>> st;
    for (int i = 0; i < (int)als.size(); ++i) {
        if (i >= 1 && als[i][0] != als[i - 1][0]) {
            vector<array<int, 3>> tr;
            for (auto u : st) {
                tr.push_back(u);
            }
            build();
            for (int j = 0; j < (int)tr.size(); ++j) {
                int c = tr[j][1];
                int x = get(0, c);
                ans1[tr[j][2]] = x;
                if (dp[c] != x + 1) {
                    update(c, x + 1);
                    dp[c] = x + 1;
                }
            }
            build();
            for (int j = (int)tr.size() - 1; j >= 0; --j) {
                int c = tr[j][1];
                int x = get(c + 1, 2 * n + 2);
                int y = x + ans1[tr[j][2]] + ONE;
                if (dp[c] != x + 1) {
                    update(c, x + 1);
                    dp[c] = x + 1;
                }
                ans[tr[j][2]] = max(ans[tr[j][2]], y);
            }
        }
        auto [x, t, num] = als[i];
        now[num] += t;
        if (t == -1) {
            st.insert({ch[num].first, ch[num].second, num});
        } else {
            st.erase({ch[num].first, ch[num].second, num});
        }
    }
    ll k;
    cin >> k;
    vector<int> rans(k);
    for (ll i = 0; i < k; ++i) {
        int x;
        cin >> x;
        --x;
        rans[i] = ans[x];
    }
    for (int i = 0; i < k; ++i) {
        cout << rans[i] << '\n';
    }
    return 0;
}
