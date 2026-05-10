#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> time(n);
    for (int i = 0; i < n; ++i) {
        cin >> time[i].second >> time[i].first;
    }
    sort(time.begin(), time.end());
    int ans = 1, last = time[0].first;
    for (int i = 1; i < n; ++i) {
        if (time[i].second >= last) {
            last = time[i].first;
            ans += 1;
        }
    }
    cout << ans << endl;
}
