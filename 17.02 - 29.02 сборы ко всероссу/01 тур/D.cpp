#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> ans(55);
    ans[1] = 9;
    ans[2] = 84;
    ans[3] = 972;
    ans[4] = 9936;
    ans[5] = 99792;
    ans[6] = 999324;
    ans[7] = 9991512;
    ans[8] = 99912312;
    ans[9] = 996312312;
    ans[10] = 1121414112;
    ans[11] = 12335162112;
    ans[12] = 114456966624;
    ans[13] = 1141875356544;
    int st = 11411111111111;
    /*for (int i = st; i < 1e14; ++i) {
        int flag = 1;
        int x = i;
        int sum = 0;
        int cnt = 0;
        while (flag && x != 0) {
            cnt++;
            if (x % 10 == 0) {
                flag = 0;
                continue;
            }
            sum += x % 10;
            if (i % sum != 0) {
                flag = 0;
                continue;
            }
            x /= 10;
        }
        if (flag) {
            ans[cnt] = i;
            break;
        }
    }*/
    cout << ans[n] << endl;
}
