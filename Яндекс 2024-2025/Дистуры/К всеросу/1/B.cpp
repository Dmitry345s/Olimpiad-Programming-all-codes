#include<bits/stdc++.h>

using namespace std;

map<pair<int, int>, pair<int, int>> to_ans;

void solve(int a, int b, int cnt) {
    if (b == 1) {
        to_ans[{a, b}] = {0, (a + 1) % 2};
        return;
    }
    int a1 = a - 1, b1 = b;
    int d1 = __gcd(a1, b1);
    a1 /= d1;
    b1 /= d1;
    if (to_ans.find({a1, b1}) == to_ans.end()) {
        solve(a1, b1, cnt + 1);
    }
    if (to_ans[{a1, b1}].second == 0) {
        to_ans[{a, b}] = {0, 1};
        return;
    }
    if (cnt == 0) {
        to_ans[{a, b}] = {1, 1};
        return;
    }
    int a2 = a, b2 = b - 1;
    int d2 = __gcd(a2, b2);
    a2 /= d2;
    b2 /= d2;
    if (to_ans.find({a2, b2}) == to_ans.end()) {
        solve(a2, b2, cnt + 1);
    }
    if (to_ans[{a2, b2}].second == 0) {
        to_ans[{a, b}] = {1, 1};
        return;
    }
    to_ans[{a, b}] = {-1, 0};
}

signed main() {
    //cout << 2 * 3 * 5 * 7 * 11 * 13 * 17 << endl;
    int a, b;
    cin >> a >> b;
    while (true) {
        if (a % 2 == 0) {
            cout << "A" << endl;
            a -= 1;
            int d = __gcd(a, b);
            a /= d;
            b /= d;
        } else {
            cout << "B" << endl;
            b -= 1;
            int d = __gcd(a, b);
            a /= d;
            b /= d;
        }
        string ans;
        cin >> ans;
        if (ans == "OK") {
            return 0;
        }
        if (ans == "A") {
            a -= 1;
            int d = __gcd(a, b);
            a /= d;
            b /= d;
        } else {
            b -= 1;
            int d = __gcd(a, b);
            a /= d;
            b /= d;
        }
    }
    return 0;
}
