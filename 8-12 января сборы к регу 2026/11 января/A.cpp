#include<bits/stdc++.h>

#define int long long

using namespace std;

const int LN = 61;

int solve2(int i) {
    if (i == 1) return 1;
    return solve2(i - 1) * 2 + 1;
}

int solve(int x) {
    if (x < 2) return 0;
    int now = 0;
    int in = -1;
    for (int i = LN - 1; i >= 0; --i) {
        if ((x >> i) & 1) {
            return solve2(i) + solve(x - (1ll << i));
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}
