#include<bits/stdc++.h>

using namespace std;

#define int long long

int getn(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

const int SZ = 62, MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<string>> all(8);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        all[(int)s.size() - 3].push_back(s);
        reverse(s.begin(), s.end());
        all[(int)s.size() - 3].push_back(s);
    }
    int rans = 0;
    for (int i = 0; i < (int)all.size(); ++i) {
        if ((int)all[i].size() == 0) continue;
        vector<vector<int>> cnt(SZ, vector<int> (SZ));
        sort(all[i].begin(), all[i].end());
        all[i].erase(unique(all[i].begin(), all[i].end()), all[i].end());
        for (auto t : all[i]) {
            int c1 = getn(t[0]), c2 = getn(t[(int)t.size() - 1]);
            cnt[c1][c2] += 1;
        }
        int get[SZ][SZ][SZ];
        for (int c1 = 0; c1 < SZ; ++c1) {
            for (int c2 = 0; c2 < SZ; ++c2) {
                for (int c3 = 0; c3 < SZ; ++c3) {
                    get[c1][c2][c3] = 0;
                    int sz = 0;
                    for (int c4 = 0; c4 < SZ; ++c4) {
                        sz += ((1ll * cnt[c1][c4] * cnt[c2][c4]) % MOD * 1ll * cnt[c3][c4]) % MOD;
                    }
                    get[c1][c2][c3] = sz % MOD;
                }
            }
        }
        for (int c1 = 0; c1 < SZ; ++c1) {
            for (int c2 = 0; c2 < SZ; ++c2) {
                for (int c3 = 0; c3 < SZ; ++c3) {
                    for (int c4 = 0; c4 < SZ; ++c4) {
                        rans += (((get[c1][c2][c3] * get[c1][c3][c4]) % MOD) * ((get[c1][c2][c4] * get[c2][c3][c4]) % MOD)) % MOD;
                        rans %= MOD;
                    }
                }
            }
        }
    }
    cout << rans << endl;
    return 0;
}
