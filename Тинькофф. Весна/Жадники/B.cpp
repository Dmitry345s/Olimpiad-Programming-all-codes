#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> time(k);
    for (int i = 0; i < k; ++i) {
        cin >> time[i];
    }
    sort(time.begin(), time.end());
    long long sum = 0, i = 0;
    while (sum <= n && i <= k) {
        sum += time[i];
        ++i;
    }
    cout << i - 1 << endl;
    return 0;
}
