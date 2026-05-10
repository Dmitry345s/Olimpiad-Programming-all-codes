#include<bits/stdc++.h>

#define int __int128
#define rint long long

using namespace std;

mt19937 rnd(time(0));

const int one = 1, big = 31;
const int INF = 1e9, MOD = 9223372036854775783, P = 1e6 + 3, MAX = 5;

int um(int a, int b) {
    return ((a * b) % MOD + MOD) % MOD;
}

int fpow(int a, int x) {
    int ans = 1;
    while (x >= 1) {
        if (x % 2) {
            ans = um(ans, a);
        }
        a = um(a, a);
        x /= 2;
    }
    return ans;
}

int fpowr(int a, int x) {
    if (x >= 0) return fpow(a, x);
    return fpow(fpow(a, -x), MOD - 2);
}

signed main() {
    rint n;
    cin >> n;
    string s;
    cin >> s;
    vector<pair<int, rint>> op;
    int now = 3e5;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '>') {
            now++;
            op.push_back({now, 0});
        } else if (s[i] == '<') {
            now--;
            op.push_back({now, 0});
        } else if (s[i] == '+') {
            op.push_back({now, 1});
        } else {
            op.push_back({now, -1});
        }
    }
    //cout << 0 << endl;
    vector<int> suf(n + 1);
    map<int, rint> mp;
    mp[suf.back()] += 1;
    for (int i = n - 1; i >= 0; --i) {
        ////cout << i << endl;
        ////cout << um(fpow(P, op[i].first), op[i].second) << endl;
        suf[i] = (suf[i + 1] + um(fpow(P, op[i].first), op[i].second)) % MOD;
        //cout << i << " " << suf[i] << endl;
        mp[suf[i]] += 1;
    }
    //cout << 0 << endl;
    int all = suf[0];
    long long ans = 0;
    int ch = 0;
    for (int i = 0; i < n; ++i) {
        mp[suf[i]] -= 1;
        now = suf[i];
        int now2 = um(all, fpowr(P, ch));
        int now3 = (now - now2 + MOD) % MOD;
        auto it = mp.find(now3);
        if (it != mp.end()) {
            ans += (*it).second;
        }
        if (s[i] == '<') {
            ch -= 1;
        } else if (s[i] == '>') {
            ch += 1;
        }
        //cout << now << " " << now2 << " " << now3 << " " << ans << endl;
    }
    cout << ans << endl;
}
/*5
>>-<-*/
/*#include<bits/stdc++.h>

#define int __int128
#define rint long long

using namespace std;

mt19937 rnd(time(0));

const int INF = 1e9, MOD = 1e9 + 9, P = 1e9 + 7, MAX = 5;

int um(int a, int b) {
    return a * b;
}

int fpow(int a, int x) {
    int ans = 1;
    while (x >= 1) {
        if (x % 2) {
            ans = um(ans, a);
        }
        a = um(a, a);
        x /= 2;
    }
    return ans;
}

int fpowr(int a, rint x) {
    if (x >= 0) return fpow(a, x);
    return fpow(fpow(a, -x), MOD - 2);
}

signed main() {
    rint n;
    cin >> n;
    string s;
    cin >> s;
    vector<pair<int, rint>> op;
    int now = 3e5;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '>') {
            now++;
            op.push_back({now, 0});
        } else if (s[i] == '<') {
            now--;
            op.push_back({now, 0});
        } else if (s[i] == '+') {
            op.push_back({now, 1});
        } else {
            op.push_back({now, -1});
        }
    }
    //cout << 0 << endl;
    vector<int> suf(n + 1);
    map<int, rint> mp;
    mp[suf.back()] += 1;
    //cout << op.size() << endl;
    for (rint i = n - 1; i >= 0; --i) {
        ////cout << i << endl;
        ////cout << um(fpow(P, op[i].first), op[i].second) << endl;
        suf[i] = (suf[i + 1] + um(fpow(P, op[i].first), op[i].second));
        //cout << i << " " << suf[i] << endl;
        mp[suf[i]] += 1;
    }
    //cout << 0 << endl;
    int all = suf[0];
    long long ans = 0;
    rint ch = 0;
    for (int i = 0; i < n; ++i) {
        mp[suf[i]] -= 1;
        now = suf[i];
        int now2 = um(all, fpowr(P, ch));
        int now3 = (now - now2);
        auto it = mp.find(now3);
        if (it != mp.end()) {
            ans += (*it).second;
        }
        if (s[i] == '<') {
            ch -= 1;
        } else if (s[i] == '>') {
            ch += 1;
        }
        //cout << now << " " << now2 << " " << now3 << " " << ans << endl;
    }
    cout << ans << endl;
}*/
