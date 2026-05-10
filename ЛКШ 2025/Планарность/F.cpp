#include<bits/stdc++.h>

using namespace std;
const int MAX = 100;

int x[MAX];
int all[MAX * 10][6];

mt19937 rnd(57);
mt19937 rnd2(69);

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> all[i][0] >> all[i][1] >> all[i][2] >> all[i][3] >> all[i][4] >> all[i][5];
        --all[i][0]; --all[i][2]; --all[i][4];
    }
    int cnt = 50000;
    while (cnt) {
        cnt--;
        for (int i = 0; i < n; ++i) {
            x[i] = (rnd() & 1);
        }
        for (int j = 0; j < 3 * n; ++j) {
            for (int u = 0; u < m; ++u) {
                if (!(x[all[u][0]] == all[u][1] || x[all[u][2]] == all[u][3] || x[all[u][4]] == all[u][5])) {
                    x[all[u][rnd() % 3 * 2]] ^= 1;
                    //break;
                }
            }
        }
        int fl = 1;
        for (int u = 0; u < m; ++u) {
            if (!(x[all[u][0]] == all[u][1] || x[all[u][2]] == all[u][3] || x[all[u][4]] == all[u][5])) {
                fl = 0;
                break;
            }
        }
        if (fl) {
            for (int i = 0; i < n; ++i) cout << x[i];
            return 0;
        }
    }
    cnt = 50000;
    while (cnt) {
        cnt--;
        for (int i = 0; i < n; ++i) {
            x[i] = (rnd2() & 1);
        }
        for (int j = 0; j < 3 * n; ++j) {
            for (int u = 0; u < m; ++u) {
                if (!(x[all[u][0]] == all[u][1] || x[all[u][2]] == all[u][3] || x[all[u][4]] == all[u][5])) {
                    x[all[u][rnd2() % 3 * 2]] ^= 1;
                    //break;
                }
            }
        }
        int fl = 1;
        for (int u = 0; u < m; ++u) {
            if (!(x[all[u][0]] == all[u][1] || x[all[u][2]] == all[u][3] || x[all[u][4]] == all[u][5])) {
                fl = 0;
                break;
            }
        }
        if (fl) {
            for (int i = 0; i < n; ++i) cout << x[i];
            return 0;
        }
    }
    return 0;
}
