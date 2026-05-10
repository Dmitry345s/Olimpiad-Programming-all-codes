#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int maxm = 0;
    int in = -1;
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
        if (a[i] > maxm) {
            maxm = a[i];
            in = i;
        }
    }
    if (n == 1) {
        cout << a[0] << endl;
        return 0;
    }
    vector<array<int, 3>> ls;
    vector<pair<int, int>> tg;
    if (a[0] <= a[1]) {
        ls.push_back({a[0], 0, a[0]});
        tg.push_back({0, a[0]});
    }
    for (int i = 1; i < n - 1; ++i) {
        if (a[i] <= a[i - 1]) {
            while (ls.size() > 0 && ls.back()[0] > a[i]) {
                ls.pop_back();
            }
            if (ls.size() == 0) {
                tg.push_back({i, a[i] * i});
                ls.push_back({a[i], i, a[i] * i});
            } else {
                tg.push_back({i, ls.back()[2] + (i - ls.back()[1]) * a[i]});
                ls.push_back({a[i], i, ls.back()[2] + (i - ls.back()[1]) * a[i]});
            }
        } else {
            tg.push_back({i, ls.back()[2] + a[i]});
            ls.push_back({a[i], i, ls.back()[2] + a[i]});
        }
    }
    vector<array<int, 3>> ls2;
    vector<pair<int, int>> tg2;
    if (a.back() <= a[n - 2]) {
        ls2.push_back({a.back(), n - 1, a.back()});
        tg2.push_back({n - 1, a.back()});
    }
    for (int i = n - 2; i >= 1; --i) {
        if (a[i] <= a[i + 1]) {
            while (ls2.size() > 0 && ls2.back()[0] > a[i]) {
                ls2.pop_back();
            }
            if (ls2.size() == 0) {
                tg2.push_back({i, a[i] * (n - i)});
                ls2.push_back({a[i], i, a[i] * (n - i)});
            } else {
                tg2.push_back({i, ls2.back()[2] + (ls2.back()[1] - i) * a[i]});
                ls2.push_back({a[i], i, ls2.back()[2] + (ls2.back()[1] - i) * a[i]});
            }
        } else {
            tg2.push_back({i, ls2.back()[2] + a[i]});
            ls2.push_back({a[i], i, ls2.back()[2] + a[i]});
        }
    }
    reverse(tg2.begin(), tg2.end());
    maxm = 0; in = -1;
    for (int i = 1; i < n - 1; ++i) {
        if (!(a[i] >= a[i - 1] && a[i] >= a[i + 1])) continue;
        int l2 = upper_bound(tg2.begin(), tg2.end(), pair<int, int>{i, 1ll * -1}) - tg2.begin();
        auto [j, x] = tg2[l2];
        int nowans = pref[j] - pref[i] + x;
        int l = lower_bound(tg.begin(), tg.end(), pair<int, int>{i, 1ll * -1}) - tg.begin();
        l--;
        auto [j2, x2] = tg[l];
        //cout << i << " " << j << " " << x << " " << j2 << " " << x2 << " " << nowans << " ";
        nowans += pref[i] - pref[j2 + 1] + x2;
        //cout << nowans << endl;
        if (nowans > maxm) {
            maxm = nowans;
            in = i;
        }

    }
    vector<int> tans(n);
    tans[0] = a[0];
    long long cnt = a[0];
    for (int i = 1; i < n; ++i) {
        tans[i] = min(a[i], tans[i - 1]);
        cnt += tans[i];
    }
    if (cnt > maxm) {
        maxm = cnt;
        in = 0;
    }
    vector<int> tans2(n);
    long long cnt2 = a.back();
    tans2.back() = a.back();
    for (int i = n - 2; i >= 0; --i) {
        tans2[i] = min(a[i], tans2[i + 1]);
        cnt2 += tans2[i];
    }
    if (cnt2 > maxm) {
        maxm = cnt2;
        in = n - 1;
    }
    vector<int> ans(n);
    ans[in] = a[in];
    for (int i = in + 1; i < n; ++i) {
        ans[i] = min(a[i], ans[i - 1]);
    }
    for (int i = in - 1; i >= 0; --i) {
        ans[i] = min(a[i], ans[i + 1]);
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
