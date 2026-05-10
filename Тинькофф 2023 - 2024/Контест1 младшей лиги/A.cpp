#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int x, y;
    cin >> x >> y;
    string ans;
    int c = (int) '0';
    while (x != 0 && y != 0) {
        if (x % 10 == y % 10) {
            ans.push_back(char(x % 10 + c));
            ans.push_back(char(x % 10 + c));
        } else {
            ans.push_back(char(max(x % 10, y % 10) + c));
        }
        x /= 10;
        y /= 10;
    }
    while (x != 0) {
        ans.push_back(char(x % 10 + c));
        x /= 10;
    }
    while (y != 0) {
        ans.push_back(char(y % 10 + c));
        y /= 10;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    return 0;
}
