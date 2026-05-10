#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int maxm = -1e5, num = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > maxm) {
            maxm = a[i];
            num = i;
        }
    }
    int i = -1, j = 0;
    long long cnt = a[0], ans = a[0], l = -1, r = 0;
    while (i < n && j < n) {
        if (ans < cnt) {
            l = i;
            r = j;
            ans = cnt;
        }
        if (cnt >= 0) {
            j += 1;
            cnt += a[j];
        } else {
            i += 1;
            cnt -= a[i];
        }
    }
    if (l + 2 <= r + 1) {
        cout << l + 2 << " " << r + 1 << " " << ans << endl;
    } else {
        cout << num + 1 << " " << num + 1 << " " << maxm << endl;
    }
    return 0;
}
