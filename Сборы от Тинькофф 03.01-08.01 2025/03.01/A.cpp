#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int w, h;
        cin >> w >> h;
        if (w < h) {
            swap(w, h);
        }
        if (h % 2 == 0) {
            h--;
        }
        a[i] = h;
    }
    sort(a.begin(), a.end());
    int need = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] >= (2 * need - 1)) {
            need += 1;
        }
    }
    cout << need - 1 << endl;
    return 0;
}
