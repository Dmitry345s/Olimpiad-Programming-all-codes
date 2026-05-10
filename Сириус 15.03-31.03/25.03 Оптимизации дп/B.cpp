#include<bits/stdc++.h>

using namespace std;

int MAX1 = 4000, MAX2 = 800;
vector<int> dp(MAX1);
vector<int> dp2(MAX1);
vector<int> opt(MAX1);
vector<int> a(MAX1);
int n;

void get(int l, int r, int optL, int optR) {
    if (l >= r) return;
    int m = (l + r) / 2;
    int x = -1;
    for (int i = optL; i < min(m, optR) - 1; ++i) {
        if (dp[m] < dp2[i] + a[i + 1] * (m - i)) {
            dp[m] = dp2[i] + a[i + 1] * (m - i);
            x = i;
        }
    }
    get(l, m, optL, x);
    get(m + 1, r, x, optR);
}

signed main() {
    int k;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    return 0;
}
