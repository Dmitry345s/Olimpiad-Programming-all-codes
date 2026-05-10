#include<bits/stdc++.h>

using namespace std;

int MAX = 5e5 + 1;
long long mod = 998244353;
vector<int> pr(MAX, 1);
vector<long long> fc(MAX);
vector<vector<int>> pr2(MAX);

long long pow(long long a, long long x) {
    long long ans = 1;
    while (x != 0) {
        if (x % 2 == 1) {
            x -= 1;
            ans = (ans * a) % mod;
        } else {
            x /= 2;
            a = (a * a) % mod;
        }
    }
    return ans;
}

long long getc(int k, int n) {
    if (k == 0) {
        return 1;
    }
    long long f = pow(fc[k], mod - 2), s = pow(fc[n - k], mod - 2);
    return ((f * s) % mod * fc[n]) % mod;
}

void start() {
    pr[1] = 0;
    for (int i = 2; i * i < MAX; ++i) {
        if (pr[i] == 1) {
            for (int j = i * i; j < MAX; j += i) {
                pr[j] = max(pr[j], i);
            }
            pr[i] = i;
        }
    }
    fc[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        if (pr[i] == 1) {
            pr[i] = i;
        }
        int x = i;
        int cnt = 0;
        while (x % pr[i] == 0) {
            x /= pr[i];
            cnt++;
        }
        pr2[i] = pr2[x];
        pr2[i].push_back(cnt);
        fc[i] = (fc[i - 1] * i) % mod;
    }
}

signed main() {
    start();
    long long n, c;
    cin >> n >> c;
    long long ans = 0;
    cout << pr[4] << endl;
    for (int i = 1; i <= c; ++i) {
        long long cnt = 0;
        long long now = 1;
        for (int j = 0; j < pr2[i].size(); ++j) {
            cnt += pr2[i][j];
            now = (now * pow(fc[pr2[i][j]], mod - 2)) % mod;
        }
        cout << endl;
        now = (now * pow(n, cnt)) % mod;
        cout << cnt << " " << now << endl;
        ans = (ans + now) % mod;
    }
    cout << ans << endl;
    return 0;
}
