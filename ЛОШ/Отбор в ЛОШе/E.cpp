#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<pair<int, int>> b;
    b.push_back({a[0], 1});
    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1]) {
            b.back().second += 1;
        } else {
            b.push_back({a[i], 1});
        }
    }
    if (b.size() == 1) {
        cout << b[0].second - 1 << endl;
        return 0;
    }
    int ans = max(b[0].second, b.back().second);
    for (int i = 1; i < b.size() - 1; ++i) {
        ans = max(ans, b[i].second);
        if (b[i].second == 1 && b[i - 1].first == b[i + 1].first) {
            ans = max(ans, b[i - 1].second + b[i + 1].second);
        }
    }
    cout << ans << endl;
    return 0;
}
