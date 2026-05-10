#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n1, n2, n3, n4;
    cin >> n1 >> n2 >> n3 >> n4;
    int x = (n3 + n1 + n4) / 2;
    int y = (n3 + n4 + n2) / 2;
    if (x * 2 != n1 + n3 + n4 || y * 2 != n3 + n4 + n2) {
        cout << "impossible" << endl;
        return 0;
    }
    double maxm = -1;
    vector<int> mask(4);
    for (int i = 0; i <= n3; ++i) {
        for (int j = 0; j <= n4; ++j) {
            int nn1 = x - i - j;
            int nn2 = y - j - (n3 - i);
            if (nn1 < 0 || nn2 < 0 || nn1 > n1 || nn2 > n2) continue;
            double c = x * y - double(i * i + j * j + (n3 - i) * (n3 - i) + (n4 - j) * (n4 - j)) / 2;
            if (c >= maxm) {
                maxm = c;
                mask = {i, nn1, j, nn2};
            }
        }
    }
    if (maxm == -1) {
        cout << "impossible" << endl;
        return 0;
    }
    for (int i = 0; i < mask[0]; ++i) {
        cout << 3;
    }
    for (int i = 0; i < mask[1]; ++i) {
        cout << 1;
    }
    for (int i = 0; i < mask[2]; ++i) {
        cout << 4;
    }
    for (int i = 0; i < mask[3]; ++i) {
        cout << 2;
    }
    for (int i = 0; i < n3 - mask[0]; ++i) {
        cout << 3;
    }
    for (int i = 0; i < n1 - mask[1]; ++i) {
        cout << 1;
    }
    for (int i = 0; i < n4 - mask[2]; ++i) {
        cout << 4;
    }
    for (int i = 0; i < n2 - mask[3]; ++i) {
        cout << 2;
    }
    return 0;
}
