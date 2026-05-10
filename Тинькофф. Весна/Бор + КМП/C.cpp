#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    string p = t + "#" + s;
    int n = t.size() + s.size() + 1;
    vector<int> z(n);
    z[0] = 0;
    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < n && p[z[i]] == p[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
    vector<int> ans;
    int q = t.size();
    for (int i = q; i < n; ++i) {
        if (z[i] == q) {
            ans.push_back(i - q - 1);
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
