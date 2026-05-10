#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;
int cnt1[MAX];
int cnt2[MAX];

int ch(int d, int x, int y, int k) {
    int ch1 = 1;
    int now = 0;
    for (int i = 0; i < x; ++i) {
        if (now + cnt1[i] > k) {
            now = 0;
            ch1++;
            if (cnt1[i] > k) {
                ch1 = d + 1;
                break;
            }
        }
        now += cnt1[i];
    }
    int ch2 = 1;
    now = 0;
    for (int i = 0; i < y; ++i) {
        if (now + cnt2[i] > k) {
            now = 0;
            ch2++;
            if (cnt2[i] > k) {
                ch2 = d + 1;
                break;
            }
        }
        now += cnt2[i];
    }
    cout << x << " " << y << " " << d << endl;
    return ((ch1 <= d && x >= d) || (ch2 <= d && y >= d));
}

signed main() {
    int x, y, g, d;
    cin >> x >> y >> d >> g;
    for (int i = 0; i < g; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        cnt1[x]++;
        cnt2[y]++;
    }
    int l = 0, r = g;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (ch(d, x, y, m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << endl;
}
