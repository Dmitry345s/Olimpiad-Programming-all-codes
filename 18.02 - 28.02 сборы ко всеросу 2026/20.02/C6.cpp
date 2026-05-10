#include<bits/stdc++.h>

#define int long long

using namespace std;
using ull = unsigned long long;

const int MOD = 1e9 + 7;
const int MAX = 5e5 + 1;
const int P = 1e9 + 7;

int fpow(int a, int x) {
    int ans = 1;
    while(x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

int get(char c) {
    return c - '(' + 1;
}

int f[MAX];
int rf[MAX];
ull ps[MAX];

int c(int k, int n) {
    return f[n] * rf[n - k] % MOD * rf[k] % MOD;
}

int mn = 0;
int cnt = 0;
vector<int> all[MAX];
int pr[MAX];

pair<ull, pair<int, int>> solve(string & s, int l, int r) {
    //cout << l << " " << r << endl;
    int n = r - l;
    if (n == 2) {
        ull nhs = get('(') * P + get(')');
        return {nhs, {2, 1}};
    }
    int bl = pr[l];
    vector<int> allbl;
    int j = lower_bound(all[bl].begin(), all[bl].end(), l) - all[bl].begin();
    //cout << j << endl;
    while (j < (int)all[bl].size() && all[bl][j] <= r) {
        allbl.push_back(all[bl][j]);
        j++;
    }
    vector<pair<ull, pair<int, int>>> u2;
    int tt = 0;
    for (int i = 0; i < (int)allbl.size() - 1; i++) {
        int ls = allbl[i];
        int rs = allbl[i + 1];
        if (ls == l && rs == r) {
            ls++;
            rs--;
            tt = 1;
        }
        auto tr = solve(s, ls, rs);
        u2.push_back(tr);
        ls = rs;
    }
    sort(u2.begin(), u2.end());
    ull nsh = 0;
    if (tt) {
        nsh += get('(');
    }
    for (auto [hs, sz] : u2) {
        nsh *= ps[sz.first];
        nsh += hs;
    }
    if (tt) {
        nsh *= P;
        nsh += get(s.back());
    }
    int yy = (int)u2.size();
    int ql = 0;
    int allans = 1;
    while (ql < (int)u2.size()) {
        int st = ql;
        while (ql < (int)u2.size() && pair<ull, int>{u2[ql].first, u2[ql].second.first} == pair<ull, int>{u2[st].first, u2[st].second.first}) {
            ql++;
        }
        int cnt1 = ql - st;
        int ans1 = u2[st].second.second;
        allans = (allans * fpow(ans1, cnt1) % MOD * c(cnt1, yy)) % MOD;
        yy -= cnt1;
    }
    return {nsh, {n, allans}};
}

signed main() {
    f[0] = 1;
    rf[0] = 1;
    ps[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        f[i] = (f[i - 1] * i) % MOD;
        rf[i] = (rf[i - 1] * fpow(i, MOD - 2)) % MOD;
        ps[i] = (ps[i - 1] * P);
    }
    int n;
    cin >> n;
    n *= 2;
    string s;
    cin >> s;
    int bl = 0;
    pr[0] = 0;
    all[0].push_back(0);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            bl++;
        } else {
            bl--;
        }
        pr[i + 1] = bl;
        all[bl].push_back(i + 1);
    }
    auto ans = solve(s, 0, n);
    cout << ans.second.second << endl;
    return 0;
}

