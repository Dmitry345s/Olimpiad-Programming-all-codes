#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> b;
    vector<vector<int>> a(k, vector<int> (n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            b.push_back({a[i][j], i});
        }
        sort(a[i].begin(), a[i].end());
    }
    sort(b.begin(), b.end());
    vector<long long> ans(k);
    for (int i = 0; i < b.size(); ++i) {
        int l = lower_bound(a[b[i].second].begin(), a[b[i].second].end(), b[i].first) - a[b[i].second].begin();
        ans[b[i].second] += i - l;
    }
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
