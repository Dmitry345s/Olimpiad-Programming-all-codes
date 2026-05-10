#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = 0; i < 10; ++i) {
        vector<int> gt;
        for (int j = 0; j < n; ++j) {
            if ((j >> i) & 1) {
                gt.push_back(j);
            }
        }
        if (gt.empty()) continue;
        cout << "CHECK ";
        for (int v : gt) {
            cout << v + 1 << " ";
        }
        cout << endl;
        for (int u = 0; u < (int)gt.size(); ++u) {
            int x;
            cin >> x;
            --x;
            ans[x] += (1 << i);
        }
    }
    cout << "RESULT ";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
