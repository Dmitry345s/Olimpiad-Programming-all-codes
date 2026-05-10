#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 4e6 + 1;

bitset<MAX> bag;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    bag[0] = 1;
    for (int i = 0; i < n; ++i) {
        bag |= (bag << a[i]);
    }
    vector<int> all;
    for (int x = bag._Find_next(-1); x < MAX; x = bag._Find_next(x)) {
        all.push_back(x);
    }
    cout << all[(int)all.size() / 2] << endl;
    return 0;
}
