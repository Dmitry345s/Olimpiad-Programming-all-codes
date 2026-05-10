#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int a, b, c;
    cin >> a >> b >> c;
    int n;
    cin >> n;
    int ga = a * b / __gcd(a, b);
    int gb = b * c / __gcd(b, c);
    int gc = c * a / __gcd(c, a);
    int all = (__int128)ga * gb / __gcd(ga, gb);
    vector<int> pr;
    for (int i = ga; i < all; i += ga) {
        pr.push_back(i);
    }
    for (int i = gb; i < all; i += gb) {
        pr.push_back(i);
    }
    for (int i = gc; i < all; i += gc) {
        pr.push_back(i);
    }
    sort(pr.begin(), pr.end());
    if ((int)pr.size() == 0) {
        cout << -1 << endl;
        return 0;
    }
    n--;
    int y = n / (int)pr.size();
    __int128 now = (__int128)y * all;
    int t = n % (int)pr.size();
    now += pr[t];
    if (now > INF) {
        cout << -1 << endl;
    } else {
        cout << (long long)now << endl;
    }
    return 0;
}
