#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5;
int tr[MAX];

const int MOD = 1e9 + 7;

int fc[MAX], rfc[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int maxm = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxm = max(a[i], maxm);
    }
    if (maxm <= 2) {
        vector<int> pref(n + 1);
        pref[0] = 0;
        tr[0] = 1;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
            tr[pref[i + 1]] = 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 18; ++j) {
                int x = (1 << j) + pref[i];
                if (x < MAX && tr[x]) ans++;
            }
        }
        cout << ans << endl;
    } else if (n <= 5000) {
        vector<int> b;
        for (int i = 0; i < n; ++i) {
            for (int x = 0; x < 30; ++x) {
                b.push_back(a[i] + x);
            }
        }
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        vector<int> a2(n);
        for (int i = 0; i < n; ++i) {
            a2[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        }
        vector<int> used((int)b.size(), -1);
        long long cnt = 0;
        for (int l = 0; l < n; ++l) {
            vector<int> all;
            for (int r = l; r < n; ++r) {
                int x = a2[r];
                while (used[x] != -1) {
                    used[all.back()] = used[x];
                    swap(all.back(), all[used[x]]);
                    all.pop_back();
                    used[x] = -1;
                    x += 1;
                }
                used[x] = (int)all.size();
                all.push_back(x);
                if ((int)all.size() == 1) {
                    cnt++;
                }
            }
            for (auto c : all) {
                used[c] = -1;
            }
        }
        cout << cnt << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = fpow(2, a[i]);
        }
        vector<int> pref(n + 1);
        map<int, int> mp;
        pref[0] = 0;
        mp[0] = 1;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
            mp[pref[i + 1]] = 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 100; ++j) {
                int x = fpow(2, j) + pref[i];
                if (mp.find(x) != mp.end()) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

