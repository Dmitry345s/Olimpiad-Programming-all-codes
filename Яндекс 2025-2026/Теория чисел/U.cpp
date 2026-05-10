#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 1;
int now[MAX];
int cnt[MAX];
vector<int> all[MAX];
int to_tr[MAX];
int cntt[MAX];

void sieve() {
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; j += i) {
            all[j].push_back(i);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    sieve();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if (now[a] == 0) {
            for (int v : all[a]) {
                cnt[v]++;
                cntt[v]++;
            }
        }
        now[a] = 1;
    }
    int ans = 1;
    while (now[1] != 1 && ans < 10) {
        for (int i = 0; i < MAX; ++i) {
            to_tr[i] = cnt[i] * cntt[i];
        }
        for (int i = MAX - 1; i >= 1; --i) {
            for (int j = 2 * i; j < MAX; j += i) {
                to_tr[i] -= to_tr[j];
            }
        }
        for (int i = 0; i < MAX; ++i) {
            if (to_tr[i] && !now[i]) {
                for (int v : all[i]) {
                    cnt[v]++;
                }
                now[i] = 1;
            }
        }
        ans++;
    }
    if (ans == 10) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
