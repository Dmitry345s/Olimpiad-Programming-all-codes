#include<bits/stdc++.h>

//#define int long long

using namespace std;

const int A = 26;
array<int, A> em;
const int MAX = 500;
const int INF = 1000;

int tr(int i) {
    if (i < 10) return 1;
    if (i < 100) return 2;
    return 3;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.tie(0);
    for (int i = 0; i < A; ++i) {
        em[i] = 0;
    }
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<pair<int, int>> dp[n][n + 1];
    for (int i = 1; i < q; ++i) {
        for (int l = 0; l < n; ++l) {
            vector<array<int, A>> cnt(i, array<int, A> (em));
            vector<int> mxs(i, 0);
            int dif = 0;
            for (int r = l + i; r <= n; r += i) {
                for (int u = 0; u < i; ++u) {
                    cnt[u][s[r - i + u] - 'a']++;
                    if (cnt[u][s[r - i + u] - 'a'] > mxs[u]) {
                        mxs[u] = cnt[u][s[r - i + u] - 'a'];
                    }
                }
                int dif = 0;
                for (int u = 0; u < i; ++u) {
                    dif += mxs[u];
                }
                int len = i + tr((r - l) / i);
                if (len > q) continue;
                dp[l][r].push_back({len, r - l - dif});
            }
        }
    }
    int ndp[q + 1];
    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            fill(ndp, ndp + q + 1, INF);
            for (auto [len, dif] : dp[l][r]) {
                ndp[len] = min(ndp[len], dif);
            }
            dp[l][r].clear();
            for (int i = 0; i <= q; ++i) {
                if (ndp[i] != INF) {
                    dp[l][r].push_back({i, ndp[i]});
                }
            }
        }
    }
    //if (n > 350) assert(0);
    vector<vector<int>> ans(n, vector<int> (q + 1, INF));
    for (int i = 0; i < n; ++i) {
        for (auto [len, ch] : dp[0][i + 1]) {
            ans[i][len] = min(ans[i][len], ch);
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int nq = 0; nq <= min(i + 2, q); ++nq) {
            for (int j = 0; j < i; ++j) {
                for (auto [len, ch] : dp[j + 1][i + 1]) {
                    if (len > nq) break;
                    if (ans[i][nq] > ans[j][nq - len] + ch) {
                        ans[i][nq] = ans[j][nq - len] + ch;
                    }
                }
            }
        }
    }
    int rans = INF;
    for (int i = 0; i <= q; ++i) {
        rans = min(rans, ans[n - 1][i]);
    }
    if (rans == INF) {
        cout << -1 << endl;
    } else {
        cout << rans << endl;
    }
    return 0;
}
