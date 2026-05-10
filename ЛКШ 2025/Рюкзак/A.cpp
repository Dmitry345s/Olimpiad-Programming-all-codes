#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e8 + 1;
int cnt[MAX];

void upd(int v) {
    cnt[v]++;
    if (cnt[v] == 3) {
        cnt[v] -= 2;
        upd(2 * v);
    }
}

signed main() {
    int n, c;
    cin >> n >> c;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        upd(a);
    }
    bitset<MAX> bag;
    bag[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            bag |= (bag << i);
        }
    }
    for (int i = 1; i <= c; ++i) {
        cout << bag[i];
    }
    cout << endl;
    return 0;
}
