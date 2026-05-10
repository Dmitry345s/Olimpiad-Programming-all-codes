#include<bits/stdc++.h>

//#define int long long

using namespace std;
using ll = long long;

const int C = 5000;
const int MAXC = 3e5 + 1;

vector<int> b[MAXC];

const int MAX = 1e5 + 1;
int tree[MAX];

void add(int i, int x) {
    for (; i < MAX; i |= (i + 1)) {
        tree[i] += x;
    }
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[a[i]].push_back(i);
        pref[i + 1] = pref[i] + a[i];
    }
    vector<array<int, 4>> s1;
    vector<vector<array<int, 3>>> s2(C);
    vector<ll> ans(q);
    vector<int> ms(q);
    for (int i = 0; i < q; ++i) {
        int l, r, m;
        cin >> l >> r >> m;
        r++;
        ms[i] = m;
        if (m >= C) {
            for (int j = m; j < MAXC; j += m) {
                s1.push_back({j, i, l, r});
            }
            ans[i] = pref[r] - pref[l];
        } else {
            s2[m].push_back({l, r, i});
        }
    }
    //cout << -1 << endl;
    sort(s1.begin(), s1.end());
    int u = 0;
    for (auto [uu, in, l, r] : s1) {
        //cout << uu << " " << in << " " << l << " " << r << endl;
        while (u < uu) {
            for (auto v : b[u]) {
                //cout << v << endl;
                add(v, 1);
            }
            u++;
        }
        ans[in] -= 1ll * ms[in] * (r - l - (get(r - 1) - get(l - 1)));
    }
    for (int y = 0; y < C; ++y) {
        if (s2[y].empty()) continue;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i] % y;
        }
        for (auto [l, r, in] : s2[y]) {
            ans[in] = pref[r] - pref[l];
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}
