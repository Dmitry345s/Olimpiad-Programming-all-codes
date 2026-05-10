#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6, LN = 20;
int sp[MAX][LN];
int sp2[MAX][LN];

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        sp[i][0] = a[i];
    }
    for (int j = 1; j < LN; ++j) {
        for (int i = 0; i < n; ++i) {
            sp[i][j] = __gcd(sp[i][j - 1], sp[min(n - 1, i + (1 << (j - 1)))][j - 1]);
        }
    }
    for (int i = 0; i < n; ++i) {
        sp2[i][0] = a[i];
    }
    for (int j = 1; j < LN; ++j) {
        for (int i = 0; i < n; ++i) {
            sp2[i][j] = __gcd(sp2[i][j - 1], sp2[max(0, i - (1 << (j - 1)))][j - 1]);
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int now = i;
        for (int j = LN - 1; j >= 0; --j) {
            if (now >= n) break;
            if (sp[now][j] % a[i] == 0) {
                now = min(n, now + (1 << j));
            }
        }
        ans[i] += now - i;
        now = i;
        for (int j = LN - 1; j >= 0; --j) {
            if (now < 0) break;
            if (sp2[now][j] % a[i] == 0) {
                now = max(-1, now - (1 << j));
            }
        }
        ans[i] += i - now;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] - 1 << " ";
    }
    cout << endl;
    return 0;
}
