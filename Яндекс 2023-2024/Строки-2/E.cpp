#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s = "ed", s2 = "fE";
    vector<string> ans;
    ans.push_back(s);
    ans.push_back(s2);
    int last = 0;
    while (ans.size() < 3000) {
        int now = ans.size();
        for (int i = last; i < now; ++i) {
            string t = ans[i];
            ans.push_back(t + s);
            ans.push_back(t + s2);
        }
        last = now;
    }
    int k;
    cin >> k;
    for (int i = last; i < last + k; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
