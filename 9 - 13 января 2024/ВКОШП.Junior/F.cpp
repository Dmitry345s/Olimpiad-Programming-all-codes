#include<iostream>
#include<vector>

using namespace std;

int main() {
    long long n, m, a, b, c;
    cin >> n;
    vector<int> v(n);
    int x = -1;
    int y = -1;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] - 1 > i) {
            x = max(x, v[i] - 1 - i);
        } else {
            y = max(y, i - v[i] + 1);
        }
    }
    cout << min(x, y) * 2 + max(x, y) << endl;
    return 0;
}
