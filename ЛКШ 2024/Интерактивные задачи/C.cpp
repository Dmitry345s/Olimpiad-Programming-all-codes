#include<bits/stdc++.h>

using namespace std;

const int MAX = 4e4;
int primes[MAX];

void sieve() {
    fill(primes, primes + MAX, 1);
    primes[0] = 0;
    primes[1] = 0;
    for (int i = 2; i < MAX; ++i) {
        if (primes[i] == 1) {
            for (int j = 2 * i; j < MAX; j += i) {
                primes[j] = 0;
            }
        }
    }
}

const long long INF = 1e18;

signed main() {
    sieve();
    int t;
    cin >> t;
    while (t--) {
        vector<int> ch(MAX);
        vector<int> now2(MAX);
        for (int _ = 0; _ < 22; ++_) {
            long long now = 1;
            int last = MAX;
            for (int j = 2; j < MAX; ++j) {
                if (primes[j] && now2[j] != -1) {
                    long long n_now = 1;
                    for (int i2 = 0; i2 < ch[j] + 1; ++i2) {
                        n_now *= j;
                    }
                    if (now <= INF / n_now) {
                        now *= n_now;
                        last = j;
                    } else {
                        continue;
                    }
                }
            }
            cout << "? " << now << endl;
            long long ans;
            cin >> ans;
            for (int j = 2; j <= last; ++j) {
                int cnt = 0;
                while (primes[j] && ans % j == 0) {
                    cnt++;
                    ans /= j;
                }
                if (cnt == ch[j]) {
                    now2[j] = -1;
                } else if (now2[j] != -1) {
                    ch[j] = cnt;
                }
                //cout << j << " " << ch[j] << endl;
            }
        }
        long long ans = 1;
        for (int i = 0; i < MAX; ++i) {
            ans *= (ch[i] + 1);
        }
        if (ans == 1) {
            cout << "! " << 8 << endl;
        } else {
            cout << "! " << ans * 2 << endl;
        }
    }
    return 0;
}
