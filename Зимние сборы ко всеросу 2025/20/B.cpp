#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 20;
vector<int> g[MAX];
int used[MAX], is_pr[MAX];

int try_kuhn(int v) {
    if (used[v] == 1) return 0;
    used[v] = 1;
    for (int to : g[v]) {
        if (is_pr[to] == -1) {
            is_pr[to] = v;
            return 1;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(is_pr[to])) {
            is_pr[to] = v;
            return 1;
        }
    }
    return 0;
}

const int MAX2 = 2e5 + 1;
int ch[MAX2];
int cnt[2 * MAX2];

void add(int i, int x) {
    for (; i < 2 * MAX2; i |= (i + 1)) {
        cnt[i] += x;
    }
}

int get(int i) {
    int sum = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        sum += cnt[i];
    }
    return sum;
}

int solve(int l, int r) {
    if (l + 1 == r) {
        if (ch[l] == 1) return 1;
        return 0;
    }
    int m = (l + r) / 2;
    int ans = solve(l, m) + solve(m, r);
    int now = 0;
    for (int i = m; i < r; ++i) {
        now += ch[i];
        add(now + MAX2, 1);
    }
    now = 0;
    for (int i = m - 1; i >= l; --i) {
        now += ch[i];
        int now2 = -now + MAX2;
        ans += (r - m) - get(now2);
    }
    now = 0;
    for (int i = m; i < r; ++i) {
        now += ch[i];
        add(now + MAX2, -1);
    }
    //cout << l << " " << r << " " << ans << endl;
    return ans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < k; ++i) {
            int c;
            cin >> c;
            g[i].clear();
            for (int u = 0; u < k; ++u) {
                if (c % a[u] == 0) {
                    g[i].push_back(u);
                }
            }
        }
        int ans = 0;
        fill(is_pr, is_pr + k, -1);
        for (int i = 0; i < k; ++i) {
            fill(used, used + k, 0);
            ans += try_kuhn(i);
        }
        if (ans == k) {
            ch[j] = 1;
        } else {
            ch[j] = -1;
        }
    }
    int ans = solve(0, n);
    cout << ans << endl;
    return 0;
}
