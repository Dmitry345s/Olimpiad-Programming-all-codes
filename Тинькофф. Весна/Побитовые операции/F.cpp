#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> b(1e5, {1e9, -1});
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        b[x - 1] = {i, x};
    }
    sort(b.begin(), b.end());
    vector<int> ans;
    int j = 0;
    while (j < 1e5 && b[j].first != 1e9) {
        ans.push_back(b[j].second);
        ++j;
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
