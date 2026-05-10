#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> s(n);
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    vector<array<array<int, 3>, 3>> all(1);
    array<int, 3> hhh = {0, 0, 0};
    array<array<int, 3>, 3> hhhh = {hhh, hhh, hhh};
    all[0] = hhhh;
    for (int i = 0; i < n; ++i) {
        all.back()[s[i] - 1][t[i] - 1]++;
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int x = (a ^ 3 ^ b);
        vector<array<array<int, 3>, 3>> alln;
        for (auto cnt : all) {
            if (cnt[a][b] == 0) {
                if (cnt[a][a] == 0) {
                    if (cnt[a][x] == 0) {
                        cout << "NO" << endl;
                        return 0;
                    } else {
                        cnt[a][x]--;
                        cnt[b][x]++;
                        alln.push_back(cnt);
                    }
                } else {
                    cnt[a][a]--;
                    cnt[b][a]++;
                    alln.push_back(cnt);
                    cnt[a][a]++;
                    cnt[b][a]--;
                    if (cnt[a][x] != 0) {
                        cnt[a][x]--;
                        cnt[b][x]++;
                        alln.push_back(cnt);
                        cnt[a][x]++;
                        cnt[b][x]--;
                    }
                }
            } else {
                cnt[a][b]--;
                cnt[b][b]++;
                alln.push_back(cnt);
            }
        }
        sort(alln.begin(), alln.end());
        alln.erase(unique(alln.begin(), alln.end()), alln.end());
        all = alln;
    }
    for (auto cnt : all) {
        if (cnt[0][0] + cnt[1][1] + cnt[2][2] == n) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
