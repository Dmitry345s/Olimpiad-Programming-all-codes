#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> get(int a) {
    int i = 2;
    vector<pair<int, int>> ans;
    while (i * i <= a) {
        if (a % i == 0) {
            ans.push_back({(i - 1) / 2, (a / i + 1) / 2});
        }
        ++i;
    }
    return ans;
}

vector<pair<int, int>> get2(int a) {
    int i = 2;
    vector<pair<int, int>> ans;
    while (i * i <= a) {
        if (a % i == 0) {
            ans.push_back({(a / i + 1) / 2, (i - 1) / 2});
            int ch1 = (i + 1) / 2, ch2 = (a / i - 1) / 2;
            if (ch1 == ch2) {
                ans.push_back({ch1, ch2});
            }
        }
        ++i;
    }
    return ans;
}

signed main() {
    int x;
    cin >> x;
    vector<pair<int, int>> y = get(2 * x - 1);
    vector<pair<int, int>> z = get2(2 * x - 3);
    if (x == 3) {
        z.push_back({1, 1});
    }
    cout << y.size() + z.size() << endl;
    for (int i = 0; i < (int)y.size(); ++i) {
        cout << y[i].first << " " << y[i].second << endl;
    }
    for (int i = 0; i < (int)z.size(); ++i) {
        cout << z[i].first << " " << z[i].second << endl;
    }
    return 0;
}
