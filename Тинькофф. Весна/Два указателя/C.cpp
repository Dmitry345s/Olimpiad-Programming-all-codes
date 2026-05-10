#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> d;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        d.push_back({l, -1});
        d.push_back({r, 1});
    }
    sort(d.begin(), d.end());
    int i = 0, j = 0;
    vector<pair<int, int>> ans;
    while (j < d.size()) {
        int cnt = -1;
        j += 1;
        while (j < d.size() && cnt != 0) {
            cnt += d[j].second;
            j += 1;
        }
        ans.push_back({d[i].first, d[j - 1].first});
        i = j;
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
