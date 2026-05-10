#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        string s;
        cin >> s;
        deque<pair<int, int>> now;
        int l = 0;
        int n = (int)s.size();
        while (l < n) {
            int st = l;
            while (l < n && s[l] == s[st]) {
                l++;
            }
            //cout << st << " " << l << endl;
            now.push_back({s[st] - '0', l - st});
        }
        int fl = 0;
        int ch = 0;
        while (true) {
            if (now.empty()) {
                fl = ch;
                break;
            }
            //cout << now.front().first << " " << now.front().second << " " << now.back().first << " " << now.back().second << endl;
            if (now.front().first != ch && now.back().first != ch) {
                fl = ch;
                break;
            }
            if (now.front().first != ch || now.front().first > now.back().second) {
                now.back().second -= 2;
                int nc = 0;
                if (now.back().second <= 0) {
                    now.pop_back();
                    nc = 1;
                }
                if (nc && !now.empty()) {
                    now.back().second -= 1;
                    if (now.back().second == 0) {
                        now.pop_back();
                    }
                }
                ch ^= 1;
                continue;
            }
            if (now.back().first != ch || now.front().first < now.back().second) {
                now.front().second -= 2;
                int nc = 0;
                if (now.front().second <= 0) {
                    now.pop_front();
                    nc = 1;
                }
                if (nc && !now.empty()) {
                    now.front().second -= 1;
                    if (now.front().second == 0) {
                        now.pop_front();
                    }
                }
                ch ^= 1;
                continue;
            }
            if (now.back().second > 2) {
                now.back().second -= 2;
                ch ^= 1;
                continue;
            }
            if (now.front().second > 2) {
                now.front().second -= 2;
                ch ^= 1;
                continue;
            }
            if ((int)now.size() == 1) {
                now.pop_front();
                ch ^= 1;
                continue;
            }
            if (now[1].second < now[(int)now.size() - 2].second) {
                now.pop_front();
                now.front().second -= 1;
                if (now.front().second == 0) {
                    now.pop_front();
                }
                ch ^= 1;
                continue;
            }
            now.pop_back();
            now.back().second -= 1;
            if (now.back().second == 0) {
                now.pop_back();
            }
            ch ^= 1;
        }
        //cout << fl << endl;
        if (fl) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
