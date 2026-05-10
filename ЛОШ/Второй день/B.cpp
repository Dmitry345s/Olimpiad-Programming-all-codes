#include<iostream>
#include<vector>

using namespace std;

int gcd (int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int k, m;
    cin >> k >> m;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    vector<pair<int, int>> ans;
    ans.push_back({a[0], 0});
    for (int i = 1; i < m; ++i) {
        int g = a[i - 1] / gcd(a[i - 1], a[i]);
        bool flag = false;
        for (int j = 1; j < int(ans.size()); ++j) {
            if (ans[j].first - ans[j].second == g) {
                ans[j].second += 1;
                flag = true;
                break;
            }
        }
        if (!flag) {
            ans[0].first /= g;
            ans.push_back({g, 1});
        }
    }
    int t = 0;
    if (ans[0].first == 1) {
        t = 1;
    }
    for (int i = t; i < int(ans.size()); ++i) {
        cout << ans[i].first << " ";
    }
    for (int i = int(ans.size()); i < k + t; ++i) {
        cout << 1 << " ";
    }
    return 0;

}
