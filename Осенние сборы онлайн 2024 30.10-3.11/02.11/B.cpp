#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int g, r, b;
    cin >> g >> r >> b;
    map<int, int> mpn1, mpn2, mpn3;
    map<pair<int, int>, int> mp1, mp2, mp3;
    map<int, pair<int, int>> get;
    for (int i = 0; i < g; ++i) {
        int a;
        cin >> a;
        mpn1[a]++;
        int x = a;
        int last = a % 10;
        int first = a % 10;
        while (a != 0) {
            first = a % 10;
            a /= 10;
        }
        mp1[{first, last}]++;
        get[x] = {first, last};
    }
    for (int i = 0; i < r; ++i) {
        int a;
        cin >> a;
        mpn2[a]++;
        int x = a;
        int last = a % 10;
        int first = a % 10;
        while (a != 0) {
            first = a % 10;
            a /= 10;
        }
        mp2[{first, last}]++;
        get[x] = {first, last};
    }
    for (int i = 0; i < b; ++i) {
        int a;
        cin >> a;
        mpn3[a]++;
        int x = a;
        int last = a % 10;
        int first = a % 10;
        while (a != 0) {
            first = a % 10;
            a /= 10;
        }
        mp3[{first, last}]++;
        get[x] = {first, last};
    }
    int ans = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                for (int u = 0; u < 10; ++u) {
                    ans += mp1[{i, j}] * mp2[{j, k}] * mp3[{k, u}];
                }
            }
        }
    }
    //cout << ans << endl;
    for (auto [u, val] : mpn1) {
        auto [first, last] = get[u];
        ans -= mpn1[u] * mpn3[u] * mp2[{last, first}];
    }
    for (auto [u, val] : mpn2) {
        auto [first, last] = get[u];
        if (first != last) continue;
        int cnt1 = 0;
        int cnt2 = 0;
        for (int j = 0; j < 10; ++j) {
            cnt1 += mp3[{last, j}];
            cnt2 += mp1[{j, first}];
        }
        ans -= mpn1[u] * mpn2[u] * cnt1;
        ans -= cnt2 * mpn2[u] * mpn3[u];
        ans += 2 * mpn1[u] * mpn2[u] * mpn3[u];
    }
    cout << ans << endl;
    return 0;
}
