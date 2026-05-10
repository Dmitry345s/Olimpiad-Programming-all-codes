#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 1;
const int D = 7;

int d[MAX];
int s[MAX];

void solve(int sum, int n) {
    vector<int> pref(D + 1, -1);
    pref[D] = sum;
    pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        int k = d[i] / D;
        int t = d[i] % D;
        if (sum * k > s[i]) return;
        int u = s[i] - sum * k;
        if (pref[t] != -1 && pref[t] != u) return;
        pref[t] = u;
    }
    for (int i = 1; i < D; ++i) {
        if (pref[i] == -1) pref[i] = pref[i - 1];
    }
    for (int i = 0; i < D; ++i) {
        if (pref[i] > pref[i + 1]) return;
    }
    vector<int> a(D);
    for (int i = 0; i < D; ++i) {
        a[i] = pref[i + 1] - pref[i];
    }
    for (int i = 0; i < D; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    exit(0);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> d[i] >> s[i];
    }
    for (int i = 0; i < 100001; ++i) {
        solve(i, n);
    }
    return 0;
}
