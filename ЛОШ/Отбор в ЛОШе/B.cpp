#include<iostream>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    int maxm = 1e9, ans1 = 0, ans2 = 0;
    for (int i = 0; i <= n; ++i) {
        int maxm2 = ((i + 49) / 50) * a + ((n - i + 3) / 4) * b;
        if (maxm >= maxm2) {
            maxm = maxm2;
            ans1 = (i + 49) / 50;
            ans2 = (n - i + 3) / 4;
        }
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
