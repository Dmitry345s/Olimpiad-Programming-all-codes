#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, r;
    cin >> n >> r;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    long long cnt = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && d[j] - d[i] <= r) {
            j += 1;
        }
        cnt += n - j;
    }
    cout << cnt << endl;
    return 0;
}
