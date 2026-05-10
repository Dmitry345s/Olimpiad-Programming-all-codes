#include<bits/stdc++.h>

using namespace std;

signed main() {
    int MAX = 1026;
    vector<array<int, 25>> all(MAX);
    for (int i = 0; i < 25; ++i) {
        all[0][i] = 0;
    }
    for (int i = 1; i < MAX; ++i) {
        all[i] = all[i - 1];
        for (int j = 0; j < 25; ++j) {
            if (all[i][j] != 35) {
                all[i][j]++;
                break;
            }
        }
    }
    int n, p;
    cin >> n >> p;
    vector<int> used(p);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int sum = 0;
        for (int i = 0; i < 29; ++i) {
            if (s[i] == '-') continue;
            if (s[i] < 'A') {
                sum += (s[i] - '0');
            } else {
                sum += (s[i] - 'A') + 10;
            }
        }
        used[sum % p] = 1;
    }
    for (int i = 0; i < min(p, 876); ++i) {
        if (used[i] == 0) {
            for (int j = 0; j < 25; ++j) {
                if (all[i][j] <= 9) {
                    cout << all[i][j];
                } else {
                    cout << char(all[i][j] - 10 + 65);
                }
                if (j % 5 == 4 && j != 24) cout << '-';
            }
            //cout << endl;
            return 0;
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
