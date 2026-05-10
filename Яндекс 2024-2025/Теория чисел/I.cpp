#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e5 + 2;

signed main() {
    int n;
    cin >> n;
    vector<int> ch(MAX);
    for (int i = 0; i < n + 1; ++i) {
        int a;
        cin >> a;
        ch[a] = 1;
    }
    int sieve[MAX];
    for (int i = 2; i < MAX; ++i) {
        if (sieve[i] != 0) continue;
        for (int j = 2 * i; j < MAX; j += i) {
            sieve[j] = i;
        }
    }
    vector<int> ch2(MAX);
    long long ans = 0;
    for (int i = 2; i < MAX; ++i) {
        //cout << i << endl;
        int x = (i - 1) + ch2[i];
        int cnt = 0;
        for (int j = i; j < MAX; j += i) {
            if (ch[j]) {
                cnt = 1;
            }
        }
        if (cnt) {
            for (int j = i; j < MAX; j += i) {
                ch2[j] -= x;
            }
            ans += x;
        }
    }
    cout << ans << endl;
}
