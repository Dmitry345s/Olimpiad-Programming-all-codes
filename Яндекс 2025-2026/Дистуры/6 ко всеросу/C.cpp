#include<bits/stdc++.h>

//#define int long long

#pragma GCC optimize("O3","unroll-loops")

using namespace std;

void del(string & now, int y) {
    now[y] = (now[y] - '0' - 1) + '0';
    if (now[0] == '0') now.erase(now.begin());
}

string radd(string now, int y) {
    string ans = now;
    //reverse(ans.begin(), ans.end());
    if (y < 0) {
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < abs(y) - 1; ++i) {
            ans.push_back('0');
        }
        ans.push_back('1');
    } else {
        int go = 1;
        for (int i = y; i >= 0; --i) {
            int cnt = now[i] - '0' + go;
            ans[i] = cnt % 10 + '0';
            go = cnt / 10;
        }
        reverse(ans.begin(), ans.end());
        if (go) {
            ans.push_back('1');
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int d, k;
        cin >> d >> k;
        string n;
        cin >> n;
        int cnt = 0;
        string ans = n;
        for (int wh = 0; wh < d; ++wh) {
            if (n[wh] == '0') continue;
            if (min(wh, d - wh) < 101) {
                string cpn = n;
                for (int i = wh + 1; i < (int)n.size(); ++i) {
                    cpn[i] = '9';
                }
                del(cpn, wh);
                int p = max(0, cnt + d - wh - 1 - k);
                string tr = radd(cpn, (int)cpn.size() - 1 - p);
                if ((int)tr.size() > (int)ans.size()) {
                    ans = tr;
                } else if ((int)ans.size() > (int)tr.size()) {
                    ans = ans;
                } else {
                    ans = max(ans, tr);
                }
            }
            cnt += (n[wh] == '9');
        }
        cout << ans << '\n';
    }
    return 0;
}
