#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> ans(n, -1);
    set<pair<int, int>> s;
    int color = 0;
    for (int i = 0; i < n; ++i) {
        if (color == 0) {
            color++;
            s.insert({a[i], color});
            ans[i] = color;
        } else {
            set<pair<int, int>> :: iterator it;
            it = s.lower_bound({a[i], -1});
            if (it == s.begin()) {
                color++;
                s.insert({a[i], color});
                ans[i] = color;
            } else {
                --it;
                pair<int, int> c = *it;
                ans[i] = c.second;
                s.erase(it);
                s.insert({a[i], c.second});
            }
        }
    }
    cout << color << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
