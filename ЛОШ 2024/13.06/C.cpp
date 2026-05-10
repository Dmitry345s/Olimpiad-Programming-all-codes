#include<bits/stdc++.h>

using namespace std;

int pl(vector<int> a) {
    int flag = 0;
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        if (a[i] > a[i + 1]) {
            flag = 1;
            swap(a[i], a[i + 1]);
        }
    }
    if (flag == 0) {
        return 0;
    }
    return 1 + pl(a);
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < q; ++i) {
        int x, v;
        cin >> x >> v;
        --x;
        a[x] = v;
        cout << pl(a) << endl;
    }
    return 0;
}
