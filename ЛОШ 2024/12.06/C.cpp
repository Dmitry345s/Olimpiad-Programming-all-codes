#include<bits/stdc++.h>

using namespace std;

int MAX = 100;
vector<string> all(MAX);
vector<int> all2, all3;
int ans = 0;

void ch(int n, int m, string now = "") {
    if (m == 0) {
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (int)now.size(); ++j) {
                int flag2 = 1;
                for (int k = 0; k < (int)all[i].size(); ++k) {
                    if (j + k >= (int)now.size() || now[j + k] != all[i][k]) {
                        flag2 = 0;
                        break;
                    }
                }
                if (flag2) {
                    flag = 1;
                }
            }
        }
        if (flag == 0) ans++;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        now.push_back((char)(97 + i));
        ch(n, m - 1, now);
        now.pop_back();
    }
}

void ch2(int m, int m2, int now = 0) {
    if (m == m2) {
        ans++;
        cout << now << endl;
        return;
    }
    for (int i = 0; i < 2; ++i) {
        now *= 2;
        now += i;
        int flag = 1;
        for (int j = 0; j < (int)all2.size(); ++j) {
            if (all3[j] <= m + 1 && (all2[j] ^ now) % (1 << all3[j]) == 0) {
                flag = 0;
            }
        }
        if (flag) {
            ch2(m + 1, m2, now);
        }
        now /= 2;
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> all[i];
    }
    /*if (m <= 4 && n <= 10) {
        ch(n, m);
        cout << ans << endl;
        return 0;
    }*/
    if (m <= 25) {
        for (int i = 0; i < n; ++i) {
            if (all[i].size() > m) continue;
            int to = 0;
            for (int j = 0; j < (int)all[i].size(); ++j) {
                to *= 2;
                if (all[i][j] == 'b') {
                    to += 1;
                }
            }
            all2.push_back(to);
            cout << to << " " << (int)all[i].size() << endl;
            all3.push_back((int)all[i].size());
        }
        ch2(0, m);
        int all = (1 << m) - ans;
        long long rans = 1;
        int mod = 1e9 + 7;
        for (int i = 0; i < m; ++i) {
            rans = (rans * 26) % mod;
        }
        rans = (rans - ans + mod) % mod;
        cout << rans << endl;
    }
    return 0;
}
