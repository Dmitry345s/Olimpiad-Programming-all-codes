#include<bits/stdc++.h>

using namespace std;

int solve (vector<string> all, int st, int del) {
    int cnt4 = 0;
    int fl2 = 1;
    vector<string> ch;
    for (int i = 0; i < 3; ++i) {
        ch.push_back("");
        for (int j = st; j < st + del; ++j) {
            ch.back().push_back(all[i][j]);
            if (all[i][j] != 'R' && all[i][j] != 'G' && all[i][j] != 'B' && all[i][j] != 'W') {
                fl2 = 0;
            }
        }
    }
    int fl3 = 1;
    int cnt = 0;
    int maxm = 0;
    for (int i = st; i < st + del; ++i) {
        if (all[0][i] == 'W') {
            cnt++;
            int j = i;
            while (i + st < del && all[0][i] == 'W') {
                if (all[1][i] != 'W' || all[2][i] != 'W' || all[3][i] != 'W' || all[4][i] != 'W') {
                    fl3 = 0;
                }
                i++;
            }
            if (i - j > 10) {
                fl3 = 0;
            }
            maxm = max(maxm, i - j);
        }
    }
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    for (int i = st; i < st + del; ++i) {
        if (ch[0][i] == 'R') cnt1++;
        if (ch[1][i] == 'G') cnt2++;
        if (ch[2][i] == 'B') cnt3++;
    }
    int sum = (cnt1 + cnt2 + cnt3 > (del * 3) / 2 - 3 * maxm);
    return (sum >= 1 && fl2 && fl3 && cnt <= 1);
}

signed main() {
    vector<string> all(5);
    for (int i = 0; i < 5; ++i) {
        cin >> all[i];
    }
    //cout << 0 << endl;
    int fl = 0;
    for (int i = 0; i < 10; ++i) {
        fl |= solve(all, i, 20);
    }
    for (int i = 15; i < 20; ++i) {
        fl |= solve(all, 0, i);
        fl |= solve(all, 0, i);
        fl |= solve(all, 30 - i, i);
    }
    if (fl == 1) {
        cout << "Yes" << endl;
        return 0;
    }
    cout << "No" << endl;
    vector<vector<char>> ans(5, vector<char> (30, '.'));
    for (int i = 5; i < 25; ++i) {
        ans[0][i] = 'R';
        ans[1][i] = 'G';
        ans[2][i] = 'B';
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 30; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}
