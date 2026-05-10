#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int A = 100;

unsigned long long fpow(unsigned __int128 a, unsigned long long x, unsigned long long mod) {
    unsigned long long ans = 1;
    while (x) {
        if (x % 2) {
            ans = (a * ans) % mod;
        }
        a = (a * a) % mod;
        x /= 2;
    }
    return ans;
}

mt19937 rnd(123);

int ch(unsigned long long p) {
    unsigned long long m = p - 1;
    int cnt = 0;
    while (m % 2 == 0) {
        m /= 2;
        cnt++;
    }
    int fl = 1;
    for (int i = 2; i < A; ++i) {
        unsigned long long x = rnd() % p;
        if (x == 0) continue;
        unsigned long long u = fpow(x, m, p);
        int fl2 = (u == 1 || u == p - 1);
        for (int j = 0; j < cnt - 1; ++j) {
            u = ((unsigned __int128)u * u) % p;
            if (u == p - 1) {
                fl2 = 1;
            }
        }
        if (!fl2) {
            fl = 0;
        }
    }
    return fl;
}

const int K = 1e5 + 1, C = 1e9 + 7;
__int128 now[K];

unsigned long long f(__int128 x, unsigned long long p) {
    unsigned __int128 cc = (x + C) % p;
    return (cc * cc) % p;
}

vector<__int128> get(unsigned long long n) {
    if (ch(n)) {
        return {n};
    }
    if (n <= (long long)1e10) {
        vector<__int128> ans;
        unsigned long long x = n;
        for (long long i = 2; i * i <= n; ++i) {
            while (x % i == 0) {
                ans.push_back(i);
                x /= i;
            }
        }
        if (x != 1) {
            ans.push_back(x);
        }
        return ans;
    }
    now[0] = rnd() % n;
    for (int i = 1; i < K; ++i) {
        now[i] = f(now[i - 1], n);
    }
    for (int l = 1; l < K / 2; ++l) {
        __int128 uu = (__int128)now[l] - (__int128)now[2 * l];
        __int128 tt = (uu + n) % n;
        __int128 u = __gcd(tt, (__int128)n);
        if (u != 1) {
            vector<__int128> ans = get(n / u);
            vector<__int128> anans = get(u);
            for (__int128 v : anans) ans.push_back(v);
            return ans;
        }
        if (u == n) break;
    }
    return get(n);
}

signed main() {
    //cout << (long long)ch(3) << endl;
    unsigned __int128 n = 0;
    char c;
    while (cin >> c) {
        n *= 10;
        n += c - '0';
    }
    --n;
    vector<__int128> ans = get(n);
    sort(ans.begin(), ans.end());
    cout << (long long)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        ans[i]--;
        string now;
        while (ans[i] != 0) {
            now.push_back(ans[i] % 10 + '0');
            ans[i] /= 10;
        }
        reverse(now.begin(), now.end());
        cout << now << " ";
    }
    cout << endl;
    return 0;
}

/*364870227143809*/
