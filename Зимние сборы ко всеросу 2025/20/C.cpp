#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(1488);

signed main() {
    freopen("4.txt", "w", stdout);
    int n = 100, m = 6;
    array<int, 5> xs;
    for (int i = 0; i < 5; ++i) {
        while (true) {
            xs[i] = rnd() % n + 1;
            int flag = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (xs[j] == xs[i]) flag = 1;
            }
            if (!flag) break;
        }
    }
    //cout << xs[0] << " " << xs[1] << " " << xs[2] << " " << xs[3] << endl;
    //cout << 0 << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int add = 0;
            if (j >= 6) {
                int x5 = xs[3];
                for (int u = 0; u < 10; ++u) {
                    x5 = rnd() % n + 1;
                }
                while (x5 == i || x5 == xs[0] || x5 == xs[1] || x5 == xs[2]) {
                    x5 = rnd() % n + 1;
                }
                cout << x5 << " " << add << " ";
                continue;
            }
            int mask = j;
            for (int k = 0; k < 3; ++k) {
                if (i == xs[k]) {
                    if (!((mask >> k) & 1) && !((mask == 2 && k == 2) || (mask == 4 && k == 1))) {
                        add += (1 << k);
                    }
                    mask |= (1 << k);
                }
            }
            add = min(add, m - j);
            int flag = 0;
            for (int k = 0; k < 3; ++k) {
                if (((mask >> k) & 1) == 0) {
                    cout << xs[k] << " " << add << " ";
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                int x5 = xs[3];
                for (int u = 0; u < 10; ++u) {
                    x5 = rnd() % n + 1;
                }
                while (x5 == i || x5 == xs[0] || x5 == xs[1] || x5 == xs[2]) {
                    x5 = rnd() % n + 1;
                }
                cout << x5 << " " << add << " ";
            }
        }
        cout << endl;
    }
    /*freopen("2.txt", "w", stdout);
    int n = 100, m = 2;
    array<int, 3> xs = {1, 2, 3};
    /*for (int i = 0; i < 3; ++i) {
        while (true) {
            xs[i] = rnd() % n + 1;
            int flag = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (xs[j] == xs[i]) flag = 1;
            }
            if (!flag) break;
        }
    }
    //cout << xs[0] << " " << xs[1] << " " << xs[2] << " " << xs[3] << endl;
    //cout << 0 << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j >= 2) {
                int x5 = xs[2];
                if (i == xs[2]) x5 = 4;
                cout << x5 << " " << 0 << " ";
                continue;
            }
            if (j == 0) {
                if (i == xs[0]) {
                    cout << xs[1] << " " << 1 << " ";
                } else {
                    cout << xs[0] << " " << 0 << " ";
                }
            }
            if (j == 1) {
                if (i == xs[1]) {
                    int x5 = xs[2];
                    if (i == xs[2]) x5 = 4;
                    cout << x5 << " " << 1 << " ";
                    continue;
                } else {
                    cout << xs[1] << " " << 0 << " ";
                }
            }
        }
        cout << endl;
    }*/
    return 0;
}
