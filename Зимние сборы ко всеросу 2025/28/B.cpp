#include<bits/stdc++.h>

#define int long long

using namespace std;

set<int> ans;
const int LN = 29;
map<int, int> anses;

void solve(int mask, int n, int now, int minm) {
    if (now > LN) {
        ans.insert(mask);
        anses[mask] = 0;
        return;
    }
    int anss;
    int fl = 0;
    if (mask >= minm && (int)ans.size() < n) {
        if (anses.find(mask) == anses.end()) {
            cout << "? " << mask << endl;
            cin >> anss;
            anses[mask] = anss;
        } else {
            anss = anses[mask];
        }
        if ((anss >> (LN - now)) & 1ll) {
            fl = 1ll;
        }
        if ((anss >> (LN - now)) == 0) {
            int cnt = 1ll;
            while (cnt <= (LN - now) && ((anss >> (LN - now - cnt)) & 1ll)) {
                cnt++;
            }
            //cout << cnt << endl;
            if (anss == (1ll << (LN - now)) - 1ll) {
                ans.insert(anss ^ mask);
                anses[anss ^ mask] = 0;
            } else {
                ans.insert(mask ^ anss);
                anses[mask ^ anss] = 0;
                int u = (mask ^ (((1ll << (cnt - 1ll)) - 1ll) << (LN - now - cnt + 1ll)));
                solve(u, n, now + cnt, max(minm, u));
            }
        }
    }
    int mask2 = (mask ^ (1ll << (LN - now)));
    if (mask2 >= minm && (int)ans.size() < n) {
        if (anses.find(mask2) == anses.end() && fl == 0) {
            cout << "? " << mask2 << endl;
            cin >> anss;
            anses[mask2] = anss;
        } else if (fl == 1ll) {
            anss = (anss ^ (1ll << (LN - now)));
        } else {
            anss = anses[mask2];
        }
        if ((anss >> (LN - now)) == 0) {
            int cnt = 1ll;
            while (cnt <= (LN - now) && ((anss >> (LN - now - cnt)) & 1ll)) {
                cnt++;
            }
            //cout << cnt << endl;
            if (anss == (1ll << (LN - now)) - 1ll) {
                ans.insert(anss ^ mask2);
                anses[anss ^ mask2] = 0;
            } else {
                ans.insert(mask2 ^ anss);
                anses[mask2 ^ anss] = 0;
                int u = (mask2 ^ (((1ll << (cnt - 1ll)) - 1ll) << (LN - now - cnt + 1ll)));
                solve(u, n, now + cnt, max(minm, u));
            }
        }
    }
}

signed main() {
    int n;
    cin >> n;
    solve(0, n, 0, 0);
    cout << "! ";
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
