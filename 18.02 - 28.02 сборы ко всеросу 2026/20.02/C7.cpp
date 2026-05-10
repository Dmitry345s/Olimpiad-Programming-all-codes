#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 3e5 + 1;

int fpow(int a, int x) {
    int ans = 1;
    while(x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

int f[MAX];
int rf[MAX];

int c(int k, int n) {
    return f[n] * rf[n - k] % MOD * rf[k] % MOD;
}

int mn = 0;
map<string, int> mp;
map<int, string> mp2;

string do_good(string s, int n) {
    if (mp.find(s) != mp.end()) return s;
    if (n == 2) {
        mp[s] = mn;
        mp2[mn] = s;
        mn++;
        return s;
    }
    int bl = 0;
    string now;
    vector<int> u;
    int tt = 0;
    for (int i = 0; i < n; ++i) {
        now.push_back(s[i]);
        if (s[i] == '(') {
            bl++;
        } else {
            bl--;
        }
        if (bl == 0) {
            if ((int)now.size() == n) {
                tt = 1;
                now.erase(now.begin());
                now.pop_back();
            }
            string yy = do_good(now, (int)now.size());
            u.push_back(mp[yy]);
            now.clear();
        }
    }
    sort(u.begin(), u.end());
    string good;
    for (int v : u) {
        for (char c : mp2[v]) {
            good.push_back(c);
        }
    }
    if (tt) {
        good.insert(good.begin(), '(');
        good.push_back(')');
    }
    if (mp.find(good) == mp.end()) {
        mp[good] = mn;
        mp2[mn] = good;
        mn++;
    }
    return good;
}

int solve(string good, int n) {
    if (n == 2) return 1;
    int bl = 0;
    vector<int> u;
    vector<int> uans;
    string now;
    for (int i = 0; i < n; ++i) {
        now.push_back(good[i]);
        if (good[i] == '(') {
            bl++;
        } else {
            bl--;
        }
        if (bl == 0) {
            if ((int)now.size() == n) {
                now.erase(now.begin());
                now.pop_back();
            }
            //cout << good << " " << now << endl;
            int nowans = solve(now, (int)now.size());
            u.push_back(mp[now]);
            uans.push_back(nowans);
            //cout << now << " " << mp[now] << " " << nowans << endl;
            now.clear();
        }
    }
    int yy = (int)u.size();
    int l = 0;
    int allans = 1;
    while (l < (int)u.size()) {
        int st = l;
        while (l < (int)u.size() && u[l] == u[st]) {
            l++;
        }
        int cnt1 = l - st;
        int ans1 = uans[st];
        allans = (allans * fpow(ans1, cnt1) % MOD * c(cnt1, yy)) % MOD;
        yy -= cnt1;
    }
    return allans;
}

signed main() {
    f[0] = 1;
    rf[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        f[i] = (f[i - 1] * i) % MOD;
        rf[i] = (rf[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    int n;
    cin >> n;
    n *= 2;
    string s;
    cin >> s;
    s = do_good(s, n);
    //cout << s << endl;
    cout << solve(s, n) << endl;
}
