#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    int cnt = 0;
    int ch = -1;
    string s;
    cin >> s;
    int mask = 0;
    for (int i = 0; i < n + 1; ++i) {
        if (s[i] == 'X') {
            ch = i;
        } else if (s[i] == 'C') {
            cnt++;
            if (ch == -1) {
                mask += (1 << i);
            } else {
                mask += (1 << (i - 1));
            }
        }
    }
    vector<int> d(((1 << n)) * (n + 1), 1e9);
    queue<pair<int, int>> q;
    d[mask * (n + 1) + ch] = 0;
    q.push({mask, ch});
    while (!q.empty()) {
        auto[i, now] = q.front();
        q.pop();
        int st = i * (n + 1) + now;
        if (now > 0) {
            int v = i * (n + 1) + now - 1;
            if (d[v] > d[st] + 1) {
                d[v] = d[st] + 1;
                q.push({i, now - 1});
            }
        }
        if (now < n) {
            int v = i * (n + 1) + now + 1;
            if (d[v] > d[st] + 1) {
                d[v] = d[st] + 1;
                q.push({i, now + 1});
            }
        }
        if (now > 1) {
            if (((i >> (now - 1)) & 1) != ((i >> (now - 2)) & 1)) {
                int v = (i ^ (3 << (now - 2))) * (n + 1) + now - 2;
                if (d[v] > d[st] + 1) {
                    d[v] = d[st] + 1;
                    q.push({(i ^ (3 << (now - 2))), now - 2});
                }
            }
        }
        if (now + 2 <= n) {
            if (((i >> now) & 1) != ((i >> (now + 1)) & 1)) {
                int v = (i ^ (3 << now)) * (n + 1) + now + 2;
                if (d[v] > d[st] + 1) {
                    d[v] = d[st] + 1;
                    q.push({(i ^ (3 << (now))), now + 2});
                }
            }
        }
    }
    cout << d[cnt + ((1 << (cnt)) - 1) * (n + 1)] << endl;
    return 0;
}
