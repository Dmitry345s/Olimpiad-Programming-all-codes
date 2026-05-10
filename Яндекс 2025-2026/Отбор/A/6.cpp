#include<bits/stdc++.h>

#pragma GCC optimize ("O3")

#define int long long

using namespace std;

const int MOD = 998244353, MAX = 2e3 + 5;

int l[MAX][MAX], u[MAX][MAX];
char f[MAX][MAX];
int pref[MAX][MAX], pref2[MAX][MAX];

int get2(int i, int j) {
    if (i == -1 || j == -1) return 0;
    return pref2[i][j];
}

vector<vector<int>> solve(int n, int m) {
    vector<vector<int>> rans(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] - pref[i][j] + (f[i][j] - '0');
            pref2[i + 1][j + 1] = pref2[i + 1][j] + pref2[i][j + 1] - pref2[i][j] + pref[i + 1][j + 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        int last = -1;
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == '/') {
                last = j;
            }
            l[i][j] = last;
        }
    }
    for (int j = 0; j < m; ++j) {
        int last = -1;
        for (int i = 0; i < n; ++i) {
            if (f[i][j] == '/') {
                last = i;
            }
            u[i][j] = last;
        }
    }
    for (int i = 0; i < n; ++i) {
        int ans = 0;
        vector<pair<int, int>> st;
        for (int j = 0; j < m; ++j) {
            int h = i - u[i][j];
            int now = pref[i + 1][j];
            while (!st.empty() && st.back().first >= h) {
                ans -= st.back().second * st.back().first;
                now += st.back().second;
                st.pop_back();
            }
            ans += now * h;
            st.push_back({h, now});
            rans[i][j] -= ans;
        }
    }
    for (int j = 0; j < m; ++j) {
        int ans = 0;
        vector<pair<int, int>> st;
        for (int i = 0; i < n; ++i) {
            int h = j - l[i][j];
            int now = pref[i][j + 1];
            while (!st.empty() && st.back().first >= h) {
                ans -= st.back().second * st.back().first;
                now += st.back().second;
                st.pop_back();
            }
            ans += now * h;
            st.push_back({h, now});
            rans[i][j] -= ans;
        }
    }
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        int ans = 0;
        vector<array<int, 4>> st;
        for (int j = 0; j < m; ++j) {
            int h = i - u[i][j];
            while (!st.empty() && st.back()[0] >= h) {
                cnt -= st.back()[1];
                ans -= st.back()[2];
                st.pop_back();
            }
            int y = -1;
            if (!st.empty()) {
                y = st.back()[3];
            }
            cnt += h * (j - y);
            int t = get2(u[i][j], j) - get2(u[i][j], y);
            ans += t;
            st.push_back({h, h * (j - y), t, j});
            rans[i][j] += pref[i + 1][j + 1] * cnt + pref2[i][j] - ans;
        }
    }
    return rans;
}

int to_ans1[MAX][MAX], to_ans2[MAX][MAX];

int anss[MAX][MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            f[i][j] = '/' + (f[i][j] != '*') * (f[i][j] - '0' + 1);
        }
    }
    vector<vector<int>> ans1 = solve(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m / 2; ++j) {
            swap(f[i][j], f[i][m - 1 - j]);
        }
    }
    vector<vector<int>> ans2 = solve(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m / 2; ++j) {
            swap(ans2[i][j], ans2[i][m - 1 - j]);
        }
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n / 2; ++i) {
            swap(f[i][j], f[n - 1 - i][j]);
        }
    }
    vector<vector<int>> ans4 = solve(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m / 2; ++j) {
            swap(ans4[i][j], ans4[i][m - 1 - j]);
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n / 2; ++i) {
            swap(ans4[i][j], ans4[n - 1 - i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m / 2; ++j) {
            swap(f[i][j], f[i][m - 1 - j]);
        }
    }
    vector<vector<int>> ans3 = solve(n, m);
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n / 2; ++i) {
            swap(f[i][j], f[n - 1 - i][j]);
            swap(ans3[i][j], ans3[n - 1 - i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        to_ans1[i][0] = ans2[i][0];
        to_ans2[i][0] = ans4[i][0];
        for (int j = 1; j < m; ++j) {
            to_ans1[i][j] = to_ans1[i][j - 1] - ans1[i][j - 1] + ans2[i][j];
            to_ans2[i][j] = to_ans2[i][j - 1] - ans3[i][j - 1] + ans4[i][j];
        }
    }
    for (int j = 0; j < m; ++j) {
        anss[0][j] = to_ans2[0][j] % MOD;
        for (int i = 1; i < n; ++i) {
            anss[i][j] = (anss[i - 1][j] - to_ans1[i - 1][j] + to_ans2[i][j] + MOD * MOD) % MOD;
        }
    }
    int full_ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            full_ans += (anss[i][j] * (f[i][j] - '0'));
        }
    }
    cout << full_ans % MOD << endl;
    return 0;
}
