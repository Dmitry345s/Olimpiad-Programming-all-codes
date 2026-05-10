#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    long long ans = 0;
    int cnt = v[0] - 1;
    for (auto u : v) {
        ans += u - cnt;
    }
    cout << n - ans;
}
