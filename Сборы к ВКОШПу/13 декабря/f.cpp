#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    vector<int> z(n);
    pair<int, int> maxes_x = {-1, -1};
    pair<int, int> maxes_y = {-1, -1};
    pair<int, int> maxes_z = {-1, -1};
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> z[i];
        if (x[i] == maxes_x.first || x[i] == maxes_x.second) {
            continue;
        } else {
            if (x[i] > maxes_x.first) {
                maxes_x[i].second = maxes_x[i].first;
                maxes_x.first = x[i];
            } else {
                maxes_x[i].second = max(maxes_x[i].second, x[i]);
            }
        }
    }
}
