#include<bits/stdc++.h>

#define int long long

using namespace std;

const int C = 109;
int len[C];

void prec() {
    len[0] = 0;
    for (int sum = 1; sum < 109; ++sum) {
        vector<vector<array<int, 2>>> dpn(sum, vector<array<int, 2>> (C, {0, 0}));
        for (int i = 1; i < 9; ++i) {
            dpn[i % sum][i][0] = 1;
        }
        dpn[(9) % sum][9][1] = 1;
        len[1] += dpn[0][sum][0] + dpn[0][sum][1];
        for (int i = 1; i < 12; ++i) {
            vector<vector<array<int, 2>>> ndp(sum, vector<array<int, 2>> (C, {0, 0}));
            int c = 9;
            for (int j = 0; j < sum; ++j) {
                for (int k = 0; k < C; ++k) {
                    for (int cc = 0; cc < 10; ++cc) {
                        if (k + cc >= C) continue;
                        if (cc < c) {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0] + dpn[j][k][1];
                        } else if (cc == c) {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0];
                            ndp[(j * cc) % sum][k + cc][1] += dpn[j][k][1];
                        } else {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0];
                        }
                    }
                }
            }
            swap(ndp, dpn);
            len[i + 1] += dpn[0][sum][0] + dpn[0][sum][1];
        }
    }
    for (int i = 1; i < 13; ++i) {
        len[i] += len[i - 1];
    }
}

int solve(string x) {
    if (x == "0") return 0;
    int ans = len[(int)x.size() - 1];
    //cout << x << endl;
    for (int sum = 1; sum < C; ++sum) {
        vector<vector<array<int, 2>>> dpn(sum, vector<array<int, 2>> (C, {0, 0}));
        for (int i = 1; i < x[0] - '0'; ++i) {
            dpn[i % sum][i][0] = 1;
        }
        dpn[(x[0] - '0') % sum][x[0] - '0'][1] = 1;
        for (int i = 1; i < (int)x.size(); ++i) {
            vector<vector<array<int, 2>>> ndp(sum, vector<array<int, 2>> (C, {0, 0}));
            int c = x[i] - '0';
            for (int j = 0; j < sum; ++j) {
                for (int k = 0; k < C; ++k) {
                    for (int cc = 0; cc < 10; ++cc) {
                        if (k + cc >= C) continue;
                        if (cc < c) {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0] + dpn[j][k][1];
                        } else if (cc == c) {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0];
                            ndp[(j * cc) % sum][k + cc][1] += dpn[j][k][1];
                        } else {
                            ndp[(j * cc) % sum][k + cc][0] += dpn[j][k][0];
                        }
                    }
                }
            }
            swap(ndp, dpn);
        }
        //cout << dpn[0][sum][0] << " " << dpn[0][sum][1] << endl;
        ans += dpn[0][sum][0] + dpn[0][sum][1];
    }
    //cout << ans << endl;
    return ans;
}

signed main() {
    prec();
    int l, r;
    cin >> l >> r;
    l -= 1;
    cout << solve(to_string(r)) - solve(to_string(l)) << endl;
    return 0;
}
