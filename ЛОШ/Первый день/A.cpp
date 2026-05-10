#include<iostream>

using namespace std;

int main() {
    long long n, a, b, c;
    cin >> n >> a >> b >> c;
    long long ans1, ans2, ans3, maxm = 0;
    for (long long i = a; i < n; i += a) {
        for (long long j = b; j < n - i; j += b) {
            long long may_maxm = (i / a) * (j / b) * ((n - i - j) / c);
            if (may_maxm >= maxm) {
                maxm = may_maxm;
                ans1 = i;
                ans2 = j;
                ans3 = n - i - j;
            }
        }
    }
    cout << ans1 << " " << ans2 << " " << ans3 << endl;
    return 0;
}
