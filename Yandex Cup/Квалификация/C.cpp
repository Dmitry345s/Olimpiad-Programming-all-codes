#include<bits/stdc++.h>

#define int long long

using namespace std;

map<int, vector<int>> mp;

vector<int> solve(vector<int> all, int l, int k) {
    if (mp.find(k) != mp.end()) return mp[k];
    if (k == 1) {
        mp[1] = {};
        return {};
    }
    for (int j = l; j > 1; --j) {
        if (k % all[j] == 0) {
            int nk = k / all[j];
            vector<int> now = solve(all, j, nk);
            if (nk == 1 || !now.empty()) {
                now.push_back(j);
                mp[k] = now;
                return now;
            }
        }
    }
    return {};
}

signed main() {
    int _ = 1;
    //cin >> _;
    while (_--) {
        int n, k;
        cin >> n >> k;
        vector<int> all;
        all.push_back(1);
        all.push_back(1);
        while (true) {
            int x = all.back() + all[(int)all.size() - 2];
            if (x > k) break;
            all.push_back(x);
        }
        vector<int> all2 = solve(all, (int)all.size() - 1, k);
        if (k != 1 && all2.empty()) {
            cout << -1 << endl;
            continue;
        }
        int cnt = 1;
        vector<int> trnow;
        for (int j = 0; j < (int)all2.size(); ++j) {
            cnt += all2[j] + 1;
            trnow.push_back(cnt);
            cnt++;
        }
        cnt--;
        if (cnt == n || cnt > n + 1) {
            cout << -1 << endl;
            continue;
        }
        if (cnt == n + 1) {
            trnow.pop_back();
        } else {
            for (int j = cnt + 2; j < n; j += 2) {
                trnow.push_back(j);
            }
        }
        cout << (int)trnow.size() << endl;
        for (int i = 0; i < (int)trnow.size(); ++i) {
            cout << trnow[i] << " ";
        }
        cout << endl;
    }
}
