#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAXM = 4e17 + 1;

map<int, int> anses;
vector<int> f = {0, 1};
int st;

int solve(int x) {
    int ans = 0;
    for (int i = (int)f.size() - 1; i > 0; --i) {
        if (x == 0) break;
        if (x - f[i] >= 0) {
            x -= f[i];
            ans += 1;
        }
    }
    return ans;
}

signed main() {
    while (f.back() < MAXM) {
        f.push_back(f[(int)f.size() - 2] + f.back());
    }
    int _;
    cin >> _;
    while (_--) {
        int x;
        cin >> x;
        int ans = 0;
        int rans = MAXM;
        vector<int> used((int)f.size() + 10);
        for (int i = (int)f.size() - 1; i > 0; --i) {
            if (x - f[i] >= 0) {
                x -= f[i];
                ans += 1;
                used[i] = 1;
            } else {
                rans = min(ans + 1 + solve(abs(x - f[i])), rans);
            }
        }
        int rans2 = ans;
        for (int u = 0; u < (int)f.size() * (int)f.size(); ++u) {
            for (int i = 0; i < (int)f.size(); ++i) {
                if (used[i] == 1) {
                    if (used[i + 1] == 1) {
                        used[i] = 0;
                        used[i + 1] = 0;
                        used[i + 2] = 1;
                        rans2 -= 1;
                    } else if (used[i + 2] == 1) {
                        if (i >= 1) {
                            used[i - 1] = -1;
                        }
                        used[i] = 0;
                        used[i + 1] = 0;
                        used[i + 2] = 0;
                        used[i + 3] = 1;
                    } else if (used[i + 2] == -1) {
                        used[i] = 0;
                        used[i + 2] = 0;
                        used[i + 1] = -1;
                        rans2 -= 1;
                    } else if (used[i + 3] == 1) {
                        used[i + 1] = -1;
                        used[i + 4] = 1;
                        used[i] = 0;
                        used[i + 3] = 0;
                    }
                }
            }
        }
        cout << min(rans, rans2) << endl;
    }
    return 0;
}
