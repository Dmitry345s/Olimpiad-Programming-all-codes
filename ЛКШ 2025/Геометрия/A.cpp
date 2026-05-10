#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 3e10 + 1;

mt19937 rnd(777);

ll getd(array<int, 3> a, array<int, 3> b) {
    int x = a[0] - b[0], y = a[1] - b[1], z = a[2] - b[2];
    return 1ll * x * x + 1ll * y * y + 1ll * z * z;
}

signed main() {
    int n;
    cin >> n;
    vector<array<int, 3>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i][0] >> all[i][1] >> all[i][2];
    }
    shuffle(all.begin(), all.end(), rnd);
    ll nowd = INF;
    while (true) {
        map<array<int, 3>, vector<int>> mp;
        int fl = 1;
        for (int i = 0; i < n; ++i) {
            int x = all[i][0], y = all[i][1], z = all[i][2];
            x /= nowd;
            y /= nowd;
            z /= nowd;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dz = -1; dz <= 1; ++dz) {
                        int nx = x + dx, ny = y + dy, nz = z + dz;
                        if (mp.find({nx, ny, nz}) == mp.end() || fl == 0) continue;
                        for (auto in : mp[{nx, ny, nz}]) {
                            ll trd = getd(all[i], all[in]);
                            if (trd < nowd) {
                                nowd = trd;
                                fl = 0;
                                break;
                            }
                        }
                    }
                }
            }
            if (fl) {
                mp[{x, y, z}].push_back(i);
            } else {
                break;
            }
        }
        if (fl) break;
    }
    cout << nowd << endl;
    return 0;
}
