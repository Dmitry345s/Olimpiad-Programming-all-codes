#include<iostream>

using namespace std;

int main() {
    long long c, p, n;
    cin >> c >> p >> n;
    long long cnt = 0, ans = 0, now = 1;
    if (c >= n) {
        cout << n << endl;
        return 0;
    }
    while (cnt < n) {
        long long h = 0;
        if (cnt < c) {
            h = (c - cnt + now - 1) / now;
        }
        ans += h;
        cnt += h * now;
        if ((n - cnt + c + now + p - 1) / (now + p) <= (n - cnt + now - 1) / now) {
            cnt -= c;
            now += p;
        } else {
            ans += (n - cnt + now - 1) / now;
            cnt += (n - cnt + now - 1) / now * now;
        }
    }
    cout << ans << endl;
    return 0;
}
