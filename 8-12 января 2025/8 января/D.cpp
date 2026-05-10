#include<bits/stdc++.h>

using namespace std;

const int NOW = 3;

array<array<int, NOW>, NOW> a;

map<pair<int, array<array<int, NOW>, NOW>>, int> mp;

int solve(int cnt, array<array<int, NOW>, NOW> b) {
    if (mp.find({cnt, b}) != mp.end()) return mp[{cnt, b}];
    array<int, NOW + 1> ans;
    for (int i = 0; i < NOW + 1; ++i) {
        ans[i] = 0;
    }
    int ch = 0;
    for (int i = 0; i < NOW; ++i) {
        if (b[cnt][i] != 0) {
            b[cnt][i]--;
            int x = solve(i, b);
            if (x < NOW + 1) {
                ans[x] = 1;
            }
            if (x == 0) {
                ch = 1;
            }
            b[cnt][i]++;
        }
    }
    int rans = ch;
    /*for (int i = 0; i < NOW + 1; ++i) {
        if (ans[i] == 0) {
            rans = i;
            break;
        }
    }*/
    mp[{cnt, b}] = rans;
    return rans;
}

signed main() {
    int n;
    cin >> n;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a[s[0] - 'a'][s.back() - 'a']++;
        mx = max(mx, max(s[0] - 'a', s.back() - 'a'));
    }
    array<int, NOW * NOW + 1> ans;
    for (int i = 0; i < NOW * NOW + 1; ++i) {
        ans[i] = 0;
    }
    for (int i = 0; i < NOW; ++i) {
        a[i][i] %= 2;
    }
    for (int i = 0; i < NOW; ++i) {
        for (int j = 0; j < NOW; ++j) {
            if (i != j) {
                int x = min(a[i][j], a[j][i]);
                a[i][j] -= x;
                a[j][i] -= x;
            }
        }
    }
    for (int i = 0; i < NOW; ++i) {
        for (int j = 0; j < NOW; ++j) {
            if (a[i][j] != 0) {
                a[i][j]--;
                int x = solve(j, a);
                if (x < NOW * NOW + 1) {
                    ans[x] = 1;
                }
                a[i][j]++;
            }
        }
    }
    int rans = 0;
    for (int i = 0; i < NOW * NOW + 1; ++i) {
        if (ans[i] == 0) {
            rans = i;
            break;
        }
    }
    if (rans != 0) {
        cout << "Artem" << endl;
    } else {
        cout << "Boris" << endl;
    }
    /*vector<vector<pair<int, array<array<int, NOW>, NOW>>>> all(NOW * NOW);
    for (auto [key, val] : mp) {
        all[val].push_back(key);
    }
    for (int i = 0; i < (int)all.size(); ++i) {
        cout << i << endl;
        for (auto [cnt, b] : all[i]) {
            cout << cnt << endl;
            for (int j = 0; j < NOW; ++j) {
                for (int k = 0; k < NOW; ++k) {
                    cout << b[j][k] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }*/
    return 0;
}
