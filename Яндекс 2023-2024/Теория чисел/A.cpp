#include<bits/stdc++.h>

using namespace std;

vector<int> get(int n) {
    vector<int> ans;
    int i = 2;
    int k = n;
    while (i * i <= k) {
        if (n % i == 0) {
            ans.push_back(i);
            n /= i;
        } else {
            ++i;
        }
    }
    if (n != 1) {
        ans.push_back(n);
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> ans = get(n);
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
