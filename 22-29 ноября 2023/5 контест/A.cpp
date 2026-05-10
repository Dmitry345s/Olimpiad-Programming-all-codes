#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> p1(n), p2(n);
    vector<int> get(n);
    for (int i = 0; i < n; ++i) {
        cin >> p1[i];
        --p1[i];
        get[p1[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> p2[i];
        --p2[i];
    }
    int cnt = 0;
    int i = 0;
    while (i < n) {
        int j = get[p2[i]];
        //cout << p1[j] << " " << p2[i] << endl;
        while (i < n && j < n && p1[j] == p2[i]) {
            ++i;
            ++j;
        }
        ++cnt;
    }
    cout << cnt << endl;
    return 0;
}
