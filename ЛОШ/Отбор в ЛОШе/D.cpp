#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n);
    pref[0] = 0;
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i - 1];
        if (a[i] > a[i - 1]) {
            pref[i] += 1;
        }
    }
    int ans = 1e9;
    for (int i = 0; i < n - k + 1; ++i) {
        ans = min(ans, pref[i + k - 1] - pref[i]);
    }
    cout << ans << endl;
    return 0;
}
