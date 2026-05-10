#include<bits/stdc++.h>

#define int long long

using namespace std;

int dist(int st, int f, int n) {
    if (st > f) {
        return n - (st - f);
    }
    return f - st;
}

const int MAX = 5e5 + 5;
int a[MAX];

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    return 0;
}
