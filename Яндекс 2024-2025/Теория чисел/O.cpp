#include<bits/stdc++.h>

using namespace std;

map<int, vector<int>> mp;

void add(int a) {
    for (int i = 1; i * i <= a; ++i) {
        if (a % i == 0) {
            mp[i].push_back(a);
            mp[a / i].push_back(a);
        }
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int minm = 2e9;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        add(a[i]);
        minm = min(minm, a[i]);
    }
    int cnt = 1;
    for (auto [key, val] : mp) {
        int gcd = 0;
        for (auto u : val) {
            gcd = __gcd(gcd, u);
        }
        if (gcd == key && gcd < minm) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
