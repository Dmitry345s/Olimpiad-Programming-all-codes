#include<bits/stdc++.h>
#define int long long

using namespace std;

int x = 0;

void get(int a, int b) {
    if (a < b) swap(a, b);
    if (a % b == 0) {
        x += (a / b) - 1;
        return;
    } else {
        x += a / b;
        get(a % b, b);
    }
}

signed main() {
    int a, b;
    cin >> a >> b;
    get(a, b);
    cout << x << endl;
    return 0;
}
