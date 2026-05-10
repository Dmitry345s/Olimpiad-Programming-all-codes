#include<bits/stdc++.h>

using namespace std;

signed main() {
    string t;
    cin >> t;
    if (t == "first") {
        int n;
        cin >> n;
        string bin;
        cin >> bin;
        vector<int> ans;
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (bin[i] == '1') {
                ans.push_back(t);
            }
            t++;
            if (i != 0 && bin[i] == '0' && bin[i - 1] == '1') {
                t--;
            }
        }
        cout << (n + 1 - (int)ans.size()) << " " << (int)ans.size() << endl;
        for (int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] + 1 << " ";
        }
        cout << endl;
    } else {
        int m, k;
        cin >> m >> k;
        vector<char> ans(m + k, '0');
        for (int i = 0; i < k; ++i) {
            int in;
            cin >> in;
            --in;
            ans[in + i] = '1';
        }
        cout << m + k - 1 << endl;
        for (int i = 0; i < m + k - 1; ++i) {
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
