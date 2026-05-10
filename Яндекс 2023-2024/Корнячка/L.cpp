#include<bits/stdc++.h>

using namespace std;

void add(int x, vector<int> & cnt, vector<int> & cnt2) {
    cnt2[cnt[x]]--;
    cnt[x]++;
    cnt2[cnt[x]]++;
}

void del(int x, vector<int> & cnt, vector<int> & cnt2) {
    cnt2[cnt[x]]--;
    cnt[x]--;
    cnt2[cnt[x]]++;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    vector<int> a2 = a;
    vector<pair<array<int, 3>, int>> qs;
    vector<array<int, 3>> qs2(q);
    vector<array<int, 3>> ups;
    int k = 2000;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 2) {
            int p, x;
            cin >> p >> x;
            --p;
            ups.push_back({p, x, a2[p]});
            a2[p] = x;
            b.push_back(x);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            qs.push_back({{(int)ups.size() / k, l / k, r}, i});
            qs2[i] = {l, r, (int)ups.size()};
        }
    }
    sort(qs.begin(), qs.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    for (int i = 0; i < (int)ups.size(); ++i) {
        ups[i][1] = lower_bound(b.begin(), b.end(), ups[i][1]) - b.begin();
        ups[i][2] = lower_bound(b.begin(), b.end(), ups[i][2]) - b.begin();
    }
    int nt = 0, nl = 0, nr = 0;
    vector<int> ans(q, -1);
    vector<int> cnt((int)b.size()), cnt2(n + 1);
    for (int i = 0; i < (int)qs.size(); ++i) {
        auto [l, r, t] = qs2[qs[i].second];
        while (nt < t) {
            auto [p, x, pref] = ups[nt];
            if (nl <= p && p < nr) {
                del(a[p], cnt, cnt2);
                add(x, cnt, cnt2);
            }
            a[p] = x;
            nt++;
        }
        while (nt > t) {
            auto [p, x, pref] = ups[nt - 1];
            if (nl <= p && p < nr) {
                del(a[p], cnt, cnt2);
                add(pref, cnt, cnt2);
            }
            a[p] = pref;
            nt--;
        }
        while (nr < r) {
            add(a[nr], cnt, cnt2);
            nr++;
        }
        while (nl > l) {
            --nl;
            add(a[nl], cnt, cnt2);
        }
        while (nr > r) {
            --nr;
            del(a[nr], cnt, cnt2);
        }
        while (nl < l) {
            del(a[nl], cnt, cnt2);
            nl++;
        }
        for (int j = 1; j <= n; ++j) {
            if (cnt2[j] == 0) {
                ans[qs[i].second] = j;
                break;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i] != -1) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
