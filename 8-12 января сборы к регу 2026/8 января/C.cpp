#include<bits/stdc++.h>

#define int long long

using namespace std;

set<array<int, 3>>::iterator get_next(set<array<int, 3>> & all, set<array<int, 3>>::iterator it) {
    auto ans = it;
    ans++;
    if (ans == all.end()) {
        ans = all.begin();
    }
    return ans;
}

set<array<int, 3>>::iterator get_prev(set<array<int, 3>> & all, set<array<int, 3>>::iterator it) {
    auto ans = it;
    if (ans == all.begin()) {
        ans = all.end();
    }
    --ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    set<array<int, 3>> all;
    all.insert({0, 1, a[0]});
    for (int i = 1; i < n; ++i) {
        //all.insert({i, 1, a[i]});
        auto it = all.end();
        --it;
        if ((*it)[2] == a[i]) {
            auto [st, len, num] = *it;
            all.erase(*it);
            all.insert({st, len + 1, a[i]});
        } else {
            all.insert({i, 1, a[i]});
        }
    }
    if ((int)all.size() > 1) {
        auto it = all.begin();
        auto itp = get_prev(all, it);
        if ((*itp)[2] == (*it)[2]) {
            auto [st1, len1, num1] = *itp;
            auto [st2, len2, num2] = *it;
            all.erase(*it);
            all.erase(*itp);
            all.insert({st1, len1 + len2, num1});
        }
    }
    set<array<int, 3>> now;
    for (auto it = all.begin(); it != all.end(); ++it) {
        auto itn = get_next(all, it);
        auto itp = get_prev(all, it);
        if ((*itn)[2] > (*it)[2] && (*itp)[2] > (*it)[2]) {
            now.insert({(*it)[1], (*it)[0], (*it)[2]});
        }
    }
    /*for (auto [st, len, num] : all) {
        cout << st << " " << len << " " << num << endl;
    }
    for (auto [len, st, num] : now) {
        cout << st << " " << len << " " << num << endl;
    }*/
    int ans = 0;
    while ((int)all.size() > 1) {
        auto [len, st, num] = *now.begin();
        now.erase(now.begin());
        auto it = all.lower_bound({st, len, num});
        auto itn = get_next(all, it);
        auto itp = get_prev(all, it);
        int u = min((*itn)[2], (*itp)[2]);
        //cout << u << endl;
        int y = min(k / len, u - num);
        //cout << y << endl;
        ans += 2 * y;
        k -= len * y;
        //cout << k << endl;
        if (k < len) {
            break;
        }
        int nlen = len, nst = st, nnum = num;
        nnum = u;
        int fl1 = 0;
        if ((*itn)[2] == u) {
            fl1 = 1;
            nlen += (*itn)[1];
        }
        int fl2 = 0;
        if (itn != itp && (*itp)[2] == u) {
            fl2 = 1;
            nlen += (*itp)[1];
            nst = (*itp)[0];
        }
        auto u1 = *it, u2 = *itn, u3 = *itp;
        //cout << fl1 << " " << fl2 << endl;
        all.erase(u1);
        if (fl1) {
            all.erase(u2);
        }
        if (fl2) {
            all.erase(u3);
        }
        all.insert({nst, nlen, nnum});
        it = all.lower_bound({nst, nlen, nnum});
        itn = get_next(all, it);
        itp = get_prev(all, it);
        if ((*itn)[2] > (*it)[2] && (*itp)[2] > (*it)[2]) {
            now.insert({nlen, nst, nnum});
        }
    }
    cout << ans << endl;
    return 0;
}

