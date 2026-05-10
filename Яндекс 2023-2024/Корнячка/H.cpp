#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
int k = 316;
vector<long long> c(MAX), c2;
vector<array<long long, 2>> b(MAX);
vector<array<int, 4>> qs(MAX);

void upd(int j) {
    int l = qs[j][0];
    int r = qs[j][1];
    long long now = qs[j][2];
    long long del = qs[j][3];
    int t = l / k;
    while (l <= r && l / k == t) {
        c2[l] += now;
        now += del;
        ++l;
    }
    if (l > r) return;
    for (int i = l / k; i < r / k; ++i) {
        b[i][0] += now;
        b[i][1] += del;
        now += k * del;
    }
    l = (r / k) * k;
    t = l / k;
    while (l <= r && l / k == t) {
        c2[l] += now;
        now += del;
        ++l;
    }
}

vector<int> ch(vector<int> tr, int n, int q) {
    c2 = c;
    vector<int> ans(n);
    int st = 0;
    b.assign((n + k - 1) / k, {0, 0});
    vector<pair<int, int>> tr2(n);
    for (int i = 0; i < n; ++i) {
        tr2[i].first = tr[i];
        tr2[i].second = i;
    }
    sort(tr2.begin(), tr2.end());
    for (int i = 0; i < q; ++i) {
        while (st < n && tr2[st].first == i) {
            int p = tr2[st].second;
            ans[p] = (c2[p] + b[p / k][0] + b[p / k][1] * (p % k) >= 0);
            st++;
        }
        upd(i);
    }
    while (st < n && tr2[st].first == q) {
        int p = tr2[st].second;
        ans[p] = (c2[p] + b[p / k][0] + b[p / k][1] * (p % k) >= 0);
        st++;
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        c[i] -= u;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2] >> qs[i][3];
        qs[i][0]--;
        qs[i][1]--;
    }
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        all[i].first = -1;
        all[i].second = q + 1;
    }
    for (int _ = 0; _ < 18; ++_) {
        vector<int> tr(n);
        for (int i = 0; i < n; ++i) {
            tr[i] = (all[i].first + all[i].second) / 2;
        }
        vector<int> news = ch(tr, n, q);
        for (int i = 0; i < n; ++i) {
            if (news[i]) {
                all[i].second = tr[i];
            } else {
                all[i].first = tr[i];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (all[i].second == q + 1) {
            cout << -1 << " ";
        } else {
            cout << all[i].second << " ";
        }
    }
    return 0;
}
