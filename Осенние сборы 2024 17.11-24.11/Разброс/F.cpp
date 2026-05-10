#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    vector<array<int, 2>> all(3);
    cin >> all[0][0] >> all[0][1] >> all[1][0] >> all[1][1] >> all[2][0] >> all[2][1];
    sort(all.begin(), all.end());
    do {
        array<int, 2> vc = {all[0][0] - all[1][0], all[0][1] - all[1][1]};
        int x = all[2][0] + vc[0], y = all[2][1] + vc[1];
        array<int, 2> vc2 = {all[0][0] - x, all[0][1] - y};
        vc[0] *= -1;
        vc[1] *= -1;
        //cout << x << " " << y << " " << vc[0] << " " << vc[1] << " " << vc2[0] << " " << vc2[1] << endl;
        if (vc[0] * vc2[0] + vc[1] * vc2[1] == 0) {
            cout << x << " " << y << endl;
            return 0;
        }
    } while (next_permutation(all.begin(), all.end()));
    return 0;
}
