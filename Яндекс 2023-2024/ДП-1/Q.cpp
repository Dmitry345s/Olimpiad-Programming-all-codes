#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }
    vector<vector<bitset<60 * 20 + 1>>> bag(n + 1, vector<bitset<60 * 20 + 1>> (sum / 3 + 1));
    bag[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum / 3; ++j) {
            for (int k = 0; k <= sum / 3; ++k) {
                int ch = bag[i - 1][j][k];
                if (j + a[i - 1] <= sum / 3) {
                    bag[i][j + a[i - 1]][k] = (bag[i][j + a[i - 1]][k] | ch);
                }
                if (k + a[i - 1] <= sum / 3) {
                    bag[i][j][k + a[i - 1]] = (bag[i][j][k + a[i - 1]] | ch);
                }
                bag[i][j][k] = (bag[i][j][k] | ch);
            }
        }
    }
    if (!bag[n][sum / 3][sum / 3]) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> rans1, rans2, rans3;
    int now1 = sum / 3, now2 = sum / 3;
    for (int i = n; i > 0; --i) {
        if (bag[i - 1][now1][now2]) {
            rans3.push_back(i);
            continue;
        }
        if (now1 >= a[i - 1] && bag[i - 1][now1 - a[i - 1]][now2]) {
            rans1.push_back(i);
            now1 -= a[i - 1];
            continue;
        }
        rans2.push_back(i);
        now2 -= a[i - 1];
    }
    cout << rans1.size() << " ";
    for (int i = 0; i < (int)rans1.size(); ++i) {
        cout << rans1[i] << " ";
    }
    cout << endl;
    cout << rans2.size() << " ";
    for (int i = 0; i < (int)rans2.size(); ++i) {
        cout << rans2[i] << " ";
    }
    cout << endl;
    cout << rans3.size() << " ";
    for (int i = 0; i < (int)rans3.size(); ++i) {
        cout << rans3[i] << " ";
    }
    cout << endl;
    return 0;
}
