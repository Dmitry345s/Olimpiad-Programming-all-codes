#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'C') {
                cnt += 1;
            }
        }
    }
    int cnt2 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'C') {
                cnt2 += 1;
            }
            if (cnt2 * 2 <= cnt) {
                cout << 1;
            } else {
                cout << 2;
            }
        }
        cout << endl;
    }
    return 0;
}
