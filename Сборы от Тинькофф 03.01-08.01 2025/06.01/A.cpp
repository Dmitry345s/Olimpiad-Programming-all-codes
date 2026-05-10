#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sort(d.begin(), d.end());
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (sum + d[i] > m) break;
        sum += d[i];
        cnt++;
    }
    cout << m + cnt << endl;
    return 0;
}
