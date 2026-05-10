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
    if (sum % 2 == 1 || n % 2 == 1) {
        cout << -1 << endl;
        return 0;
    }
    vector<vector<bitset<10001>>> bag(n + 1, vector<bitset<10001>> (n + 1));
    bag[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k <= sum; ++k) {
                if (k + a[i - 1] > sum) continue;
                int ch = bag[i - 1][j][k];
                bag[i][j + 1][k + a[i - 1]] = bag[i][j + 1][k + a[i - 1]] | ch;
                bag[i][j][k] = bag[i][j][k] | ch;
            }
        }
    }
    int now = sum / 2;
    int cnt = n / 2;
    if (!bag[n][cnt][now]) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> used(n + 1);
    for (int i = n; i > 0; --i) {
        if (!bag[i - 1][cnt][now]) {
            used[i] = 1;
            cnt -= 1;
            now -= a[i - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (used[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
