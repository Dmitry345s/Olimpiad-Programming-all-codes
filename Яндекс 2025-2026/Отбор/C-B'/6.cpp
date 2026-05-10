#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e6 + 1;
int to_ans[MAX];

void sieve() {
    for (int i = 2; i < MAX; ++i) {
        if (to_ans[i] == 0) {
            for (int j = i; j < MAX; j += i) {
                if (j / i % i == 0) {
                    to_ans[j] = -MAX;
                } else {
                    to_ans[j]++;
                }
            }
        }
    }
}

signed main() {
    sieve();
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 2; i * i * i * i * i * i * i * i <= n; ++i) {
        if (to_ans[i] == 1) {
            ans++;
        }
    }
    for (int i = 1; i * i <= n; ++i) {
        //cout << i << " " << to_ans[i] << endl;
        if (to_ans[i] == 2) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
