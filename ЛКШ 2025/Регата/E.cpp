#include<bits/stdc++.h>

#define int long long

using namespace std;

int ch(vector<int> ans) {
    int fl = 1;
    for (int i = 1; i < (int)ans.size(); ++i) {
        if (abs(ans[i] - ans[i - 1]) < 2) {
            fl = 0;
        }
    }
    return fl;
}

signed main() {
    int n;
    cin >> n;
    if (n <= 3 && n != 1) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    vector<int> ans;
    int ls = -1;
    int cnt = 0;
    set<int> all;
    for (int i = 0; i < n; ++i) {
        all.insert(i + 1);
    }
    while (cnt < n - 4) {
        auto it = all.begin();
        while (abs(*it - ls) <= 1) {
            ++it;
        }
        ls = *it;
        all.erase(it);
        ans.push_back(ls);
        cnt++;
    }
    vector<int> ok;
    int u = 0;
    for (int k : all) {
        ok.push_back(k);
    }
    do {
        for (int i = 0; i < 4; ++i) {
            ans.push_back(ok[i]);
        }
        if (ch(ans)) {
            for (int i = 0; i < n; ++i) {
                cout << ans[i] << " ";
            }
            cout << endl;
            return 0;
        }
        for (int i = 0; i < 4; ++i) {
            ans.pop_back();
        }
    } while (next_permutation(ok.begin(), ok.end()));
    return 0;
}
