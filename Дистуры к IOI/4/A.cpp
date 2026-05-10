#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 200 + 1;
int ans[MAX];
int tr = 0;
int n;
int cnt[MAX];
int pref[MAX];

int solver() {
    int l = 0, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int nadd = pref[n];
        if (m > 0) nadd -= pref[m - 1];
        int nneed = 1;
        for (int j = m - 1; j >= 1; --j) {
            int tt = nneed;
            int y = min(nneed, cnt[j]);
            nneed -= y;
            int dif = cnt[j] - y;
            nadd += dif;
            nneed = tt + nneed;
            if (nneed > n) break;
        }
        //cout << m << " " << add << endl;
        if (nneed <= cnt[0] + nadd) {
            l = m;
        } else {
            r = m;
        }
    }
    int ans = l;
    for (int i = l + 1; i <= n; ++i) {
        if (cnt[i]) ans += 1;
    }
    //cout << l << endl;
    return ans;
}

void f(int j, int y) {
    if (j == 0) {
        cnt[n - j] += y;
        pref[n - j] = max(0, cnt[n - j] - 1);
        if (n - j > 0) pref[n - j] += pref[n - j - 1];
        int nn = solver();
        ans[nn]++;
        if (ans[nn] >= MOD) ans[nn] -= MOD;
        /*for (int i = 0; i <= n; ++i) {
            cout << cnt[i] << " ";
        }
        cout << endl;
        cout << nn << endl;*/
        tr++;
        //assert(tr <= 100000000);
        cnt[n - j] -= y;
        return;
    }
    for (int lf = 0; lf <= y; ++lf) {
        cnt[n - j] += lf;
        pref[n - j] = max(0, cnt[n - j] - 1);
        if (n - j > 0) pref[n - j] += pref[n - j - 1];
        f(j - 1, y - lf);
        cnt[n - j] -= lf;
    }
}

signed main() {
    int l;
    cin >> n >> l;
    vector<int> t(l);
    for (int i = 0; i < l; ++i) {
        cin >> t[i];
    }
    sort(t.begin(), t.end());
    if (t.empty() || t[0] != 0) t.insert(t.begin(), 0);
    l = (int)t.size();
    if (l > n) {
        for (int i = 1; i <= n; ++i) {
            cout << 0 << " ";
        }
        cout << endl;
        return 0;
    }
    for (int i = 0; i < l; ++i) {
        cnt[t[i]]++;
    }
    //solver({1, 0, 2, 1, 0, 0, 2});
    f(n, n - l);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] <<  " ";
    }
    cout << endl;
    return 0;
}
