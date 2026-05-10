#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i]; --b[i];
        p[b[i]] = i;
    }
    vector<int> ch(n);
    int l = 0;
    int ans = 0;
    while (l < n) {
        int st = p[a[l]];
        //cout << l << " " << st << endl;
        while (l < n && st < n && a[l] == b[st] && !ch[st]) {
            ch[st] = 1;
            l++;
            st++;
        }
        //cout << l << " " << st << endl;
        ans++;
    }
    cout << ans << endl;
    return 0;
}
