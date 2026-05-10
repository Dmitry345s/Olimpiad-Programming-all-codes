#include<bits/stdc++.h>

# define int long long

using namespace std;

int fpow(int a, int x, int mod) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        x /= 2;
    }
    return ans;
}

signed main() {
    int p;
    cin >> p;
    int x = p - 1;
    vector<int> allps;
    for (int i = 2; i <= p; ++i) {
        if (x % i == 0) {
            allps.push_back(i);
        }
        while (x % i == 0) {
            x /= i;
        }
        if (x == 1) break;
    }
    int g = 1;
    while (true) {
        int fl = 0;
        for (auto v : allps) {
            int u = fpow(g, (p - 1) / v, p);
            if (u == 1) fl = 1;
        }
        if (!fl) break;
        g++;
    }
    int gw = fpow(g, p - 2, p);
    vector<int> ps((p - 1 + 99) / 100);
    int nowg = 1;
    int nowgw = 1;
    for (int i = 0; i < p - 1; ++i) {
        ps[(nowg - 1) / 100] += nowgw;
        nowg = (nowg * g) % p;
        nowgw = (nowgw * gw) % p;
    }
    for (int i = 0; i < (int)ps.size(); ++i) {
        cout << ps[i] % p << " ";
    }
    cout << endl;
}
