#include<bits/stdc++.h>
//#define _GLIBCXX_DEBUG

#define int long long

using namespace std;

const int MAX = 17;
const int INF = 2e16 + 1;

int prec[MAX][10][10];
int prec0[MAX][10][10];
int pows[MAX];

void f() {
    pows[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = pows[i - 1] * 10;
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j < i) {
                prec[0][i][j] = 1;
            } else {
                prec[0][i][j] = 0;
            }
            if (j < i) {
                prec0[0][i][j] = 1;
            } else {
                prec0[0][i][j] = 0;
            }
        }
    }
    for (int len = 1; len < MAX; ++len) {
        //cout << len << endl;
        for (int s = 0; s < 10; ++s) {
            //cout << s << endl;
            if (s == 0) {
                for (int j = 0; j < 10; ++j) {
                    prec[len][s][j] = 0;
                    prec0[len][s][j] = 0;
                }
                continue;
            }
            if (s == 1) {
                for (int i = len - 1; i >= 0; --i) {
                    for (int j = 0; j < 10; ++j) {
                        prec[len][s][j] += prec[i][9][j];
                    }
                    prec[len][s][9] += pows[i];
                }
                for (int j = 0; j < 10; ++j) {
                    prec0[len][s][j] = prec0[len][s - 1][j] + len * pows[len - 1];
                }
                prec0[len][s][s - 1] += pows[len];
            } else {
                for (int j = 0; j < 10; ++j) {
                    prec[len][s][j] = prec[len][s - 1][j] + len * pows[len - 1];
                }
                prec[len][s][s - 1] += pows[len];
                for (int j = 0; j < 10; ++j) {
                    prec0[len][s][j] = prec0[len][s - 1][j] + len * pows[len - 1];
                }
                prec0[len][s][s - 1] += pows[len];
            }
        }
    }
}

int solve(vector<int> d) {
    int l = 0;
    int r = INF;
    //assert(d[1] != 0);
    while (l + 1 < r) {
        //cout << l << " " << r << endl;
        int m = (l + r) / 2;
        int x = m;
        vector<int> all;
        while (x != 0) {
            all.push_back(x % 10);
            x /= 10;
        }
        vector<int> pref((int)all.size() + 1);
        pref[0] = 0;
        for (int i = 0; i < (int)all.size(); ++i) {
            pref[i + 1] = pref[i] + pows[i] * all[i];
        }
        vector<int> nd(10);
        for (int j = 0; j < 10; ++j) {
            nd[j] += prec[(int)all.size() - 1][all.back()][j];
        }
        nd[all.back()] += pref[(int)all.size() - 1];
        for (int i = (int)all.size() - 2; i >= 0; --i) {
            for (int j = 0; j < 10; ++j) {
                nd[j] += prec0[i][all[i]][j];
            }
            nd[all[i]] += pref[i];
        }
        int fl = 1;
        for (int i = 0; i < 10; ++i) {
            if (nd[i] > d[i]) {
                fl = 0;
            }
        }
        if (fl) {
            l = m;
        } else {
            r = m;
        }
    }
    return l - 1;
}

void stress() {
    vector<int> now(10);
    now[0] = 1;
    for (int i = 0; i < 10000000; ++i) {
        int x = i;
        while(x) {
            now[x % 10]++;
            x /= 10;
        }
        int u = solve(now);
        if (u == i) {
            if (i % 100000 == 0) {
                cout << "OK" << endl;
            }
            continue;
        }
        cout << i << " " << u << endl;
        return;
    }
}

signed main() {
    f();
    //stress();
    int _;
    cin >> _;
    while (_--) {
        vector<int> d(10);
        for (int i = 0; i < 10; ++i) {
            cin >> d[i];
        }
        d[0]++;
        cout << solve(d) << endl;
    }
    return 0;
}
