#include<bits/stdc++.h>

using namespace std;

const int MOD = 1000000000;

#define int long long

pair<int, int> f(string s) {
    int i = 0;
    int n = (int)s.size();
    pair<int, int> ans = {0, 0};
    while (i < n) {
        if (s[i] == 'N') {
            ans.first -= 1;
        } else if (s[i] == 'S') {
            ans.first += 1;
        } else if (s[i] == 'E') {
            ans.second += 1;
        } else if (s[i] == 'W') {
            ans.second -= 1;
        } else {
            int c = s[i] - '0';
            i += 2;
            string now;
            int bal = 1;
            while (bal != 0) {
                now.push_back(s[i]);
                i++;
                if (s[i] == '(') {
                    bal++;
                } else if (s[i] == ')') {
                    bal--;
                }
            }
            pair<int, int> add = f(now);
            ans.first += add.first * c;
            ans.second += add.second * c;
        }
        ans.first = (ans.first % MOD + MOD) % MOD;
        ans.second = (ans.second % MOD + MOD) % MOD;
        i++;
    }
    return ans;
}

signed main() {
    int _;
    cin >> _;
    while (_--) {
        string s;
        cin >> s;
        pair<int, int> ans = f(s);
        ans.first = (ans.first % MOD + MOD) % MOD;
        ans.second = (ans.second % MOD + MOD) % MOD;
        cout << ans.second + 1 << " " << ans.first + 1 << endl;
    }
    return 0;
}
