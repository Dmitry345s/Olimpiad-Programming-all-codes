#include<bits/stdc++.h>
#define int long long

using namespace std;

struct p {
    int s, c;
};

struct myst {
    p a, b, c;
};

signed main() {
    int x, y, z;
    cin >> x >> y >> z;
    int n = x + y + z;
    vector<vector<int>> a(n, vector<int> (3));
    if (x == 0 || y == 0 || z == 0) {
        a.resize(1e9);
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    vector<myst> dp(n);
    pair<multiset<pair<int, int>>, multiset<pair<int, int>>> sta, stb, stc;
    int maxm2 = max(max(a[0][0], a[0][1]), a[0][2]);
    if (a[0][0] == maxm2) {
        dp[0] = {{a[0][0], 1}, {0, 0}, {0, 0}};
        sta.first.insert({a[0][0] - a[0][1], 0});
        sta.second.insert({a[0][0] - a[0][2], 0});
    } else if (a[0][1] == maxm2) {
        dp[0] = {{0, 0}, {a[0][1], 1}, {0, 0}};
        stb.first.insert({a[0][1] - a[0][0], 0});
        stb.second.insert({a[0][1] - a[0][2], 0});
    } else if (a[0][2] == maxm2) {
        dp[0] = {{0, 0}, {0, 0}, {a[0][2], 1}};
        stc.first.insert({a[0][2] - a[0][0], 0});
        stc.second.insert({a[0][2] - a[0][1], 0});
    }
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        vector<int> dels(6);
        dels[0] += a[i][0];
        dels[1] += a[i][0];
        if (dp[j].a.c == x) {
            auto [dif, l] = *(sta.first.begin());
            dels[0] -= dif;
            if (dp[j].b.c == y) {
                auto [dif2, l2] = *(stb.second.begin());
                dels[0] -= dif2;
            }
            auto [dif3, l3] = *(sta.second.begin());
            dels[1] -= dif3;
            if (dp[j].c.c == z) {
                auto [dif4, l4] = *(stc.second.begin());
                dels[1] -= dif4;
            }
        }
        dels[2] += a[i][1];
        dels[3] += a[i][1];
        if (dp[j].b.c == y) {
            auto [dif, l] = *(stb.first.begin());
            dels[2] -= dif;
            if (dp[j].a.c == x) {
                auto [dif2, l2] = *(sta.second.begin());
                dels[2] -= dif2;
            }
            auto [dif3, l3] = *(stb.second.begin());
            dels[3] -= dif3;
            if (dp[j].c.c == z) {
                auto [dif4, l4] = *(stc.first.begin());
                dels[3] -= dif4;
            }
        }
        dels[4] += a[i][2];
        dels[5] += a[i][2];
        if (dp[j].c.c == z) {
            auto [dif, l] = *(stc.first.begin());
            dels[4] -= dif;
            if (dp[j].a.c == x) {
                auto [dif2, l2] = *(sta.first.begin());
                dels[4] -= dif2;
            }
            auto [dif3, l3] = *(stc.second.begin());
            dels[5] -= dif3;
            if (dp[j].b.c == y) {
                auto [dif4, l4] = *(stb.first.begin());
                dels[5] -= dif4;
            }
        }
        int maxm = -1e9;
        for (int l = 0; l < 6; ++l) {
            maxm = max(maxm, dels[l]);
        }
        dp[i] = dp[j];
        if (maxm == dels[0]) {
            if (dp[j].a.c == x) {
                auto [dif, l] = *(sta.first.begin());
                sta.first.erase(sta.first.begin());
                sta.second.erase({a[l][0] - a[l][2], l});
                dp[i].a.s -= a[l][0];
                dp[i].a.c -= 1;
                if (dp[j].b.c == y) {
                    auto [dif2, l2] = *(stb.second.begin());
                    stb.second.erase(stb.second.begin());
                    stb.first.erase({a[l2][1] - a[l2][0], l2});
                    dp[i].b.s -= a[l2][1];
                    dp[i].b.c -= 1;
                    dp[i].c.s += a[l2][2];
                    dp[i].c.c += 1;
                    stc.first.insert({a[l2][2] - a[l2][0], l2});
                    stc.second.insert({a[l2][2] - a[l2][1], l2});
                }
                dp[i].b.s += a[l][1];
                dp[i].b.c += 1;
                stb.first.insert({a[l][1] - a[l][0], l});
                stb.second.insert({a[l][1] - a[l][2], l});
            }
            dp[i].a.s += a[i][0];
            dp[i].a.c += 1;
            sta.first.insert({a[i][0] - a[i][1], i});
            sta.second.insert({a[i][0] - a[i][2], i});
        } else if (maxm == dels[1]) {
            if (dp[j].a.c == x) {
                auto [dif3, l3] = *(sta.second.begin());
                sta.second.erase(sta.second.begin());
                sta.first.erase({a[l3][0] - a[l3][1], l3});
                dp[i].a.s -= a[l3][0];
                dp[i].a.c -= 1;
                if (dp[j].c.c == z) {
                    auto [dif4, l4] = *(stc.second.begin());
                    stc.second.erase(stc.second.begin());
                    stc.first.erase({a[l4][2] - a[l4][0], l4});
                    dp[i].c.s -= a[l4][2];
                    dp[i].c.c -= 1;
                    dp[i].b.s += a[l4][1];
                    dp[i].b.c += 1;
                    stb.first.insert({a[l4][1] - a[l4][0], l4});
                    stb.second.insert({a[l4][1] - a[l4][2], l4});
                }
                dp[i].c.s += a[l3][2];
                dp[i].c.c += 1;
                stc.first.insert({a[l3][2] - a[l3][0], l3});
                stc.second.insert({a[l3][2] - a[l3][1], l3});
            }
            dp[i].a.s += a[i][0];
            dp[i].a.c += 1;
            sta.first.insert({a[i][0] - a[i][1], i});
            sta.second.insert({a[i][0] - a[i][2], i});
        } else if (maxm == dels[2]) {
            if (dp[j].b.c == y) {
                auto [dif3, l3] = *(stb.first.begin());
                stb.first.erase(stb.first.begin());
                stb.second.erase({a[l3][1] - a[l3][2], l3});
                dp[i].b.s -= a[l3][1];
                dp[i].b.c -= 1;
                if (dp[j].a.c == x) {
                    auto [dif4, l4] = *(sta.second.begin());
                    sta.second.erase(sta.second.begin());
                    sta.first.erase({a[l4][0] - a[l4][1], l4});
                    dp[i].a.s -= a[l4][0];
                    dp[i].a.c -= 1;
                    dp[i].c.s += a[l4][2];
                    dp[i].c.c += 1;
                    stc.first.insert({a[l4][2] - a[l4][0], l4});
                    stc.second.insert({a[l4][2] - a[l4][1], l4});
                }
                dp[i].a.s += a[l3][0];
                dp[i].a.c += 1;
                sta.first.insert({a[l3][0] - a[l3][1], l3});
                sta.second.insert({a[l3][0] - a[l3][2], l3});
            }
            dp[i].b.s += a[i][1];
            dp[i].b.c += 1;
            stb.first.insert({a[i][1] - a[i][0], i});
            stb.second.insert({a[i][1] - a[i][2], i});
        } else if (maxm == dels[3]) {
            if (dp[j].b.c == y) {
                auto [dif3, l3] = *(stb.second.begin());
                stb.second.erase(stb.second.begin());
                stb.first.erase({a[l3][1] - a[l3][0], l3});
                dp[i].b.s -= a[l3][1];
                dp[i].b.c -= 1;
                if (dp[j].c.c == z) {
                    auto [dif4, l4] = *(stc.first.begin());
                    stc.first.erase(stc.first.begin());
                    stc.second.erase({a[l4][2] - a[l4][1], l4});
                    dp[i].c.s -= a[l4][2];
                    dp[i].c.c -= 1;
                    dp[i].a.s += a[l4][0];
                    dp[i].a.c += 1;
                    sta.first.insert({a[l4][0] - a[l4][1], l4});
                    sta.second.insert({a[l4][0] - a[l4][2], l4});
                }
                dp[i].c.s += a[l3][2];
                dp[i].c.c += 1;
                stc.first.insert({a[l3][2] - a[l3][0], l3});
                stc.second.insert({a[l3][2] - a[l3][1], l3});
            }
            dp[i].b.s += a[i][1];
            dp[i].b.c += 1;
            stb.first.insert({a[i][1] - a[i][0], i});
            stb.second.insert({a[i][1] - a[i][2], i});
        } else if (maxm == dels[4]) {
            if (dp[j].c.c == z) {
                auto [dif3, l3] = *(stc.first.begin());
                stc.first.erase(stc.first.begin());
                stc.second.erase({a[l3][2] - a[l3][1], l3});
                dp[i].c.s -= a[l3][2];
                dp[i].c.c -= 1;
                if (dp[j].a.c == x) {
                    auto [dif4, l4] = *(sta.first.begin());
                    sta.first.erase(sta.first.begin());
                    sta.second.erase({a[l4][0] - a[l4][2], l4});
                    dp[i].a.s -= a[l4][0];
                    dp[i].a.c -= 1;
                    dp[i].b.s += a[l4][1];
                    dp[i].b.c += 1;
                    stb.first.insert({a[l4][1] - a[l4][0], l4});
                    stb.second.insert({a[l4][1] - a[l4][2], l4});
                }
                dp[i].a.s += a[l3][0];
                dp[i].a.c += 1;
                sta.first.insert({a[l3][0] - a[l3][1], l3});
                sta.second.insert({a[l3][0] - a[l3][2], l3});
            }
            dp[i].c.s += a[i][2];
            dp[i].c.c += 1;
            stc.first.insert({a[i][2] - a[i][0], i});
            stc.second.insert({a[i][2] - a[i][1], i});
        } else if (maxm == dels[5]) {
            if (dp[j].c.c == z) {
                auto [dif3, l3] = *(stc.second.begin());
                stc.second.erase(stc.second.begin());
                stc.first.erase({a[l3][2] - a[l3][0], l3});
                dp[i].c.s -= a[l3][2];
                dp[i].c.c -= 1;
                if (dp[j].b.c == y) {
                    auto [dif4, l4] = *(stb.first.begin());
                    stb.first.erase(stb.first.begin());
                    stb.second.erase({a[l4][1] - a[l4][2], l4});
                    dp[i].b.s -= a[l4][1];
                    dp[i].b.c -= 1;
                    dp[i].a.s += a[l4][0];
                    dp[i].a.c += 1;
                    sta.first.insert({a[l4][0] - a[l4][1], l4});
                    sta.second.insert({a[l4][0] - a[l4][2], l4});
                }
                dp[i].b.s += a[l3][1];
                dp[i].b.c += 1;
                stb.first.insert({a[l3][1] - a[l3][0], l3});
                stb.second.insert({a[l3][1] - a[l3][2], l3});
            }
            dp[i].c.s += a[i][2];
            dp[i].c.c += 1;
            stc.first.insert({a[i][2] - a[i][0], i});
            stc.second.insert({a[i][2] - a[i][1], i});
        }
    }
    cout << dp.back().a.s + dp.back().b.s + dp.back().c.s << endl;
    return 0;
}
