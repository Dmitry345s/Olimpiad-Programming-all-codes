#include<bits/stdc++.h>

using namespace std;

int ask(int x, int y, int n) {
    if (x >= n || y >= n || x < 0 || y < 0) return 0;
    cout << "examine " << x + 1 << " " << y + 1 << endl;
    string s;
    cin >> s;
    if (s == "false") {
        return 0;
    }
    return 1;
}

signed main() {
    int n, x, y;
    cin >> n >> x >> y;
    --x; --y;
    long long l = 0, r = n;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        int now = ask(x + m, y, n);
        if (now == 0) {
            r = m;
        } else {
            l = m;
        }
    }
    int right_x = x + l;
    l = 0, r = n;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        int now = ask(x - m, y, n);
        if (now == 0) {
            r = m;
        } else {
            l = m;
        }
    }
    int left_x = x - l;
    int now1 = ask((left_x + right_x) / 2, y, n);
    if (now1 == 0) {
        if (x - left_x < right_x - x) {
            right_x = (left_x * 2 + right_x - 2) / 3;
        } else {
            left_x = (left_x + 2 * right_x + 2) / 3;
        }
    } else {
    }
    return 0;
}
