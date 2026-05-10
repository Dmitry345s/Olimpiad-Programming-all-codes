#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e5 + 1, D = 51, MAX2 = 1e6 + 1;
const int INF = 2e18;
int a[MAX][3];
vector<pair<int, int>> all[MAX];
int rans[MAX2];
int d;

void solve(int l, int r) {
    //cout << l << " " << r << endl;
    if (l + 1 == r) {
        while (!all[l].empty() && all[l].back().first == r) {
            int ans = -1;
            for (int j = 0; j < 3; ++j) {
                if (a[l][j] % d == 0) {
                    ans = max(ans, a[l][j]);
                }
            }
            rans[all[l].back().second] = ans;
            all[l].pop_back();
        }
        return;
    }
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
    //cout << 0 << endl;
    vector<vector<int>> rdp;
    vector<int> dpn(d, -INF);
    dpn[0] = 0;
    rdp.push_back(dpn);
    for (int i = m; i < r; ++i) {
        vector<int> nn(d, -INF);
        for (int j = 0; j < d; ++j) {
            for (int k = 0; k < 3; ++k) {
                nn[(j + a[i][k]) % d] = max(nn[(j + a[i][k]) % d], rdp.back()[j] + a[i][k]);
            }
        }
        rdp.push_back(nn);
    }
    //cout << 0 << endl;
    for (int i = m - 1; i >= l; --i) {
        vector<int> dpnn(d, -INF);
        for (int j = 0; j < d; ++j) {
            for (int k = 0; k < 3; ++k) {
                dpnn[(j + a[i][k]) % d] = max(dpnn[(j + a[i][k]) % d], dpn[j] + a[i][k]);
            }
        }
        while (!all[i].empty() && all[i].back().first <= r) {
            int ans = -1;
            for (int j = 0; j < d; ++j) {
                ans = max(ans, dpnn[j] + rdp[all[i].back().first - m][(d - j) % d]);
            }
            rans[all[i].back().second] = ans;
            all[i].pop_back();
        }
        dpn = dpnn;
    }
}

signed main() {
    int n;
    cin >> n >> d;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        all[l].push_back({r, i});
    }
    for (int i = 0; i < n; ++i) {
        sort(all[i].rbegin(), all[i].rend());
    }
    solve(0, n);
    for (int i = 0; i < m; ++i) {
        cout << rans[i] << " ";
    }
    cout << endl;
    return 0;
}
