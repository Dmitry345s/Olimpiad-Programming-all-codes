#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int P = 1e9 + 7;
const int MAX = 5e3 + 1;
ull ps[MAX];

signed main() {
    ps[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        ps[i] = ps[i - 1] * P;
    }
    int n, m;
    cin >> n >> m;
    vector<vector<ull>> hs(n);
    vector<array<int, 3>> all;
    vector<string> ws(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        string w;
        cin >> l >> r >> w;
        --l; --r;
        all.push_back({l, r, i});
        hs[i].push_back(0);
        for (int j = 0; j < (int)w.size(); ++j) {
            hs[i].push_back(hs[i].back() * P + w[j] - 'a' + 1);
        }
        ws[i] = w;
    }
    sort(all.begin(), all.end());
    vector<vector<ull>> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i].push_back(0);
    }
    vector<string> rans(n);
    for (auto [l, r, in] : all) {
        //cout << l << " " << r << " " << ws[in] << endl;
        int mx = -1;
        int inm = -1;
        for (int i = 0; i < n; ++i) {
            if (l > (int)rans[i].size() - 1 || hs[in][min(r + 1, (int)rans[i].size()) - l] == ans[i][min(r + 1, (int)rans[i].size())] - ans[i][l] * ps[min(r + 1, (int)rans[i].size()) - l]) {
                if (mx < (int)rans[i].size()) {
                    mx = (int)rans[i].size();
                    inm = i;
                }
            }
        }
        //cout << inm << endl;
        for (int j = (int)rans[inm].size(); j <= r; ++j) {
            int y = j - l;
            if (y < 0) {
                rans[inm].push_back('a');
            } else {
                rans[inm].push_back(ws[in][y]);
            }
            ans[inm].push_back(ans[inm].back() * P + rans[inm].back() - 'a' + 1);
        }
    }
    vector<string> rrans;
    for (int i = 0; i < n; ++i) {
        if (!rans[i].empty()) {
            rrans.push_back(rans[i]);
        }
    }
    for (auto & val : rrans) {
        while ((int)val.size() < m) {
            val.push_back('a');
        }
    }
    cout << (int)rrans.size() << endl;
    for (auto val : rrans) {
        cout << val << endl;
    }
    return 0;
}
