#include<bits/stdc++.h>

using namespace std;

const int K = 200;
using ull = unsigned long long;
const int P = 179;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<string> ss(n);
    for (int i = 0; i < n; ++i) {
        cin >> ss[i];
    }
    string s;
    vector<int> to_get;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)ss[i].size(); ++j) {
            s.push_back(ss[i][j]);
        }
        s.push_back('#');
        to_get.push_back((int)s.size());
    }
    vector<int> ans(q);
    vector<vector<pair<pair<int, int>, ull>>> qs(n + 1);
    unordered_map<ull, int> mp2;
    mp2.reserve(2 * q);
    for (int _ = 0; _ < q; ++_) {
        int ls, rs;
        string now;
        cin >> ls >> rs >> now;
        ls--;
        if ((int)now.size() < K) {
            ull hs = 0;
            for (int i = 0; i < (int)now.size(); ++i) {
                hs *= P;
                hs += now[i] - 'a' + 1;
            }
            if (mp2.find(hs) == mp2.end()) {
                mp2[hs] = _;
            }
            qs[ls].push_back({{_, -1}, mp2[hs]});
            qs[rs].push_back({{_, 1}, mp2[hs]});
            continue;
        }
        string s2 = now + '*' + s;
        vector<int> z((int)s2.size());
        z[0] = 0;
        int l = 0, r = 1;
        //cout << s2 << endl;
        for (int i = 1; i < (int)s2.size(); ++i) {
            z[i] = max(0, min(r - i, z[i - l]));
            while (z[i] + i < (int)s2.size() && s2[z[i]] == s2[z[i] + i]) {
                z[i]++;
            }
            if (r < z[i] + i) {
                l = i;
                r = z[i] + i;
            }
        }
        int whr = 0;
        vector<int> ch(n);
        for (int i = (int)now.size() + 1; i < (int)s2.size() - 1; ++i) {
            while (to_get[whr] <= i - (int)now.size() - 1) {
                whr++;
            }
            if (z[i] == (int)now.size()) {
                ch[whr] = 1;
            }
        }
        for (int i = ls; i < rs; ++i) {
            ans[_] += ch[i];
        }
    }
    unordered_map<ull, int> mp;
    mp.reserve(2 * n);
    for (auto [num_type, hash1] : qs[0]) {
        //if (mp.find(hash1) == mp.end()) continue;
        ans[num_type.first] += num_type.second * mp[hash1];
    }
    vector<int> used(q + 1);
    for (int i = 0; i < n; ++i) {
        vector<ull> all;
        //all.reserve(ss[i].size() * K);
        for (int j = 0; j < (int)ss[i].size(); ++j) {
            ull now = 0;
            for (int l = j; l < min(j + K - 1, (int)ss[i].size()); ++l) {
                now *= P;
                now += ss[i][l] - 'a' + 1;
                if (mp2.find(now) == mp2.end()) continue;
                used[mp2[now]] = 1;
                all.push_back(mp2[now]);
            }
        }
        for (auto hs : all) {
            //cout << len << " " << hs << endl;
            if (used[hs]) {
                mp[hs]++;
                used[hs] = 0;
            }
        }
        for (auto [num_type, hash1] : qs[i + 1]) {
            //if (mp.find(hash1) == mp.end()) continue;
            ans[num_type.first] += num_type.second * mp[hash1];
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
