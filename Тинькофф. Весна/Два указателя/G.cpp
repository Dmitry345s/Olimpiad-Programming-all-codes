#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    map<int, int> m;
    set<pair<int, int>> s;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        m[a[i].second] = 0;
        s.erase({0, a[i].second});
        s.insert({0, a[i].second});
    }
    sort(a.begin(), a.end());
    int i = 0, j = 0;
    int ans = 1e9;
    while (i < n || j < n) {
        int minm = s.begin()->first;
        if (minm == 0 && i < n || i <= j) {
            int v = a[i].second;
            int x = m[v];
            s.erase({x, v});
            m[v] = x + 1;
            s.insert({x + 1, v});
            ++i;
        } else {
            if (minm > 0) {
                ans = min(ans, a[i - 1].first - a[j].first);
            }
            int v = a[j].second;
            int x = m[v];
            s.erase({x, v});
            m[v] = x - 1;
            s.insert({x - 1, v});
            ++j;
        }
    }
    cout << ans << endl;
    return 0;
}
