#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long sum = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt =  a[i] * (n - i);
        if (cnt > sum) {
            sum = cnt;
            ans = a[i];
        }
    }
    cout << sum << " " << ans << endl;
    return 0;
}
