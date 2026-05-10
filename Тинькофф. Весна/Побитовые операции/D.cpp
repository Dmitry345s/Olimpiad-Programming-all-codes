#include<iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        int a;
        cin >> a;
        int x = 2, num = 0;
        while (a > 0) {
            if (a % x != 0) {
                a -= (x / 2);
                num += 1;
            }
            x *= 2;
        }
        int ans = 1;
        for (int i = 0; i < num; ++i) {
            ans *= 2;
        }
        cout << ans << endl;
    }
    return 0;
}
